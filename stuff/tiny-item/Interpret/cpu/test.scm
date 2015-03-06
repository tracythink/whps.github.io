#lang scheme

; (require rnrs/base-6)
(require rnrs/mutable-pairs-6)


(include "settings.scm")
(include "machine.scm")

(define (Machine regnames ops ctrl)
  (let ((m (new-machine)))
    (for-each (lambda (reg) ((m ALLOCREG) reg)) regnames)
    ((m INSTALL-OPS) ops)
    ((m INSTALL-INQ) (assem ctrl m)) ; install instructions queue
    m))

(define (Register name)
  (let ((content UNASSIGNED))
    (define (dispatch msg)
      (cond ((eq? msg GET) content)
            ((eq? msg SET) (lambda (v) (set! content v)))
            (else (error "Register---Unkonwn request!"))))
    dispatch))

(define (get-content reg) (reg GET))
(define (set-content reg) (reg SET))

(define (Stack)
  (let ((s '()))
    (define (push x) (set! s (cons x s)))
    (define (pop)
      (if (null? s) (error "Stack.pop---Empty stack!")
	  (let ((top (car s))) (set! s (cdr s)) top)))
    (define (init) (set! s '()))
    (define (dispatch msg)
      (cond ((eq? msg PUSH) push)
            ((eq? msg POP) (pop))
            ((eq? msg INIT) (init))
            (else (error "Stack---Unknown request!"))))
    dispatch))

(define (pop s) (s POP))
(define (push s v) ((s PUSH) v))


(define (start m) (m START))
(define (get-reg-content m regname) (get-content (getreg m regname)))
(define (set-reg-content m regname) (set-content (getreg m regname)))

(define (getreg m regname) ((m GETREG) regname))

(define (new-machine) 
  (let ((pc (Register PC)) 
        (flag (Register FLAG))
        (stack (Stack)) 
        (instrq '()))
    (let ((ops (list (list INITSTACK (lambda () (stack INIT)))))
          (regs (list (list PC pc) (list FLAG flag))))
      (define (allocreg name)
        (if (assoc name '((1 2))) (error "Multiply defined register: " name)
            (set! regs (cons (list name (Register name)) regs))))
      (define (lookupreg name)
        (let ((val (assoc name regs)))
          (if val (cadr val) (error "Unkonwn register: " name))))
      (define (exec)
        (let ((instr (get-content pc)))
          (if (null? instr) 'done
              (begin ((doexec (car instr))) (exec)))))
      (define (dispatch msg)
        (cond ((eq? msg START) (set-content pc instrq) (exec))
              ((eq? msg INSTALL-INQ) (lambda (seq) (set! instrq seq)))
              ((eq? msg ALLOCREG) allocreg)
              ((eq? msg GETREG) lookupreg)
              ((eq? msg INSTALL-OPS) 
               (lambda (_ops) (set! ops (append ops _ops))))
              ((eq? msg STACK) stack)
              ((eq? msg OPERATIONS) ops)
              (else (error "new-machine---Unkonwn request!" msg)))) 
      dispatch)))

(define doexec cdr) ; because instr cons by (TAG PROC) Here is like (PROC)

(include "assem.scm")

(define (assem ctrl machine)
  (extract ctrl (lambda (instrs labs) 
                  (update instrs labs machine) instrs)))

(define (extract text recv)
  (if (null? text) (recv '() '())
      (extract (cdr text) 
               (lambda (instrs labs)
                 (let ((next (car text)))
                   (if (symbol? next)
                       (if (assoc next labs) (error "multiply label: " next)
                           (recv instrs (cons (Label next instrs) labs)))
                       (recv (cons (Instr next) instrs) labs)))))))

(define (update instrs  labs m)
  (let ((pc (getreg m PC))
        (flag (getreg m FLAG))
        (stack (getreg m STACK))
        (ops (m OPERATIONS)))
    (define (f i) 
      (setinstr i (Exec (instr-text i) labs m pc flag stack ops)))
    (for-each f instrs)))

(define (Instr text) (cons text '()))
(define (instr-text i) (car i))
(define (instr-proc i) (cdr i))
(define (setinstr i p) (set-cdr! i p))

(define Label cons)
(define (lookuplabel labs lname)
  (let ((val (assoc lname labs)))
    (if val (cdr val) (error "Undefined label!" lname))))

(define (Exec i labs m pc flag stack ops)
  (cond ((eq? (car i) ASSIGN) (Assign i m labs ops pc))
        ((eq? (car i) TEST) (Test i m labs ops pc))
        ((eq? (car i) BRANCH) (Branch i m labs flag pc))
        ((eq? (car i) GOTO) (Goto i m labs pc))
        ((eq? (car i) SAVE) (Save i m stack pc))
        ((eq? (car i) RESTORE) (Restore i m stack pc))
        ((eq? (car i) PERFORM) (Perform i m labs ops pc))
        (else "Unkonwn insruction type: " (car i))))

(define (Assign i m labs ops pc)
  (let ((target (getreg m (cadr i)))
        (valexp (cddr i)))
    (let ((valproc (if (op? valexp) 
                       (Op valexp m labs ops) 
                       (Primitive (car valexp) m labs))))
      (lambda () (set-content target (valproc)) (pc++ pc)))))

(define (pc++ pc) 
  (set-content pc (cdr (get-content pc))))

(define (Test i m labs ops flag pc)
  (let ((condition (cdr i)))
    (if (op? condition)
        (let ((proc (Op condition m labs ops)))
          (lambda () (set-content flag (proc)) (pc++ pc)))
        (error "Bad test instruction" i))))

(define (Branch i m labs flag pc)
  (let ((dest (cadr i)))
    (if (label? dest)
        (let ((instr (lookuplabel labs (cadr dest))))
          (lambda () (if (get-content flag) (set-content pc instr) (pc++ pc))))
        (error "Bad Branch instruction!" i))))

(define (Goto i m labs pc)
  (let ((dest (cadr i)))
    (cond ((label? dest)
           (let ((instr (lookuplabel labs dest)))
             (lambda () (set-content pc instr))))
          ((reg? dest) 
           (let ((reg (getreg m (cadr dest))))
             (lambda () (set-content pc (get-content reg)))))
          (else (error "Bad goto instruction: " i)))))

(define (Save i m s pc)
  (let ((reg (getreg m (cadr i))))
    (lambda () (push s (get-content reg)) (pc++ pc))))

(define (Restore i m s pc)
  (let ((reg (getreg m (cadr i))))
    (lambda () (set-content reg (pop s)) (pc++ pc))))
         
(define (Perform i m labs ops pc)
  (let ((action (cdr i)))
    (if (op? action)
        (let ((p (Op action m labs ops)))
          (lambda () (p) (pc++ pc)))
        (error "Bad Perform instruction" i))))

(define (Primitive i m labs)
  (cond ((constant? i) (lambda () (cadr i)))
        ((label? i) (lambda () (lookuplabel labs (cadr i))))
        ((reg? i) (lambda () (get-content (getreg m (cadr i)))))
        (else (error "Unkonwn instruction type!"))))

(define (tag? o c) (eq? (car o) c))
(define (reg? i) (tag? i REG))
(define (constant? i) (tag? i CONSTANT))
(define (label? i) (tag? i LABEL))

(define (Op i m labs ops)
  (let ((op (lookupprim (cadr i) ops))
        (argprocs (map (lambda (e) (Primitive e m labs)) (cdr i))))
    (lambda () (apply op (map (lambda (p) (p))) argprocs))))

(define (lookupprim symbol ops)
  (let ((val (assoc symbol ops)))
    (if val (cadr val) (error "Unknown operation" symbol))))

(define (op? i) (and (pair? i) (tag? (car i) OP)))


(define gcd-machine
  (Machine '(a b t)
           (list (list 'rem remainder) (list '= =))
           '(test-b
               (test (op =) (reg b) (reg a))
               (branch (label done))
               (assign t (op rem) (reg a) (reg b))
               (assign a (reg b))
               (assign b (reg t))
               (goto (label test-b))
             done)))
                     
             