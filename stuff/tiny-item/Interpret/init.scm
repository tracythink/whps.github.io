(define _cons (lambda (x y)  (lambda (m) (m x y))))
(define _car (lambda (z) (z (lambda (p q) p))))
(define _cdr (lambda (z) (z (lambda (p q) q))))

(define PRIMITIVE_PROCS
  (list (list 'car _car)
        (list 'cdr _cdr)
        (list 'cons _cons)
        (list 'null? null?)
        (list '+ +)
        (list '/ /)
        ; if need, add here
        ))

(define (PRIMITIVES_NAMES) (map car PRIMITIVE_PROCS))
(define (PRIMITIVES_OBJS) 
  (map (lambda (p) (list PRIMITIVE_TAG (cadr p))) PRIMITIVE_PROCS))

(define (env.setup)
  (let ((init-env (env.extend (PRIMITIVES_NAMES) 
                              (PRIMITIVES_OBJS) 
                              EMPTY_ENV)))
    (defvar! 'true #t init-env)
    (defvar! 'false #f init-env)
    init-env))

(define GLOBAL_ENV (env.setup))

(define (primitive-proc? p) (tag? p PRIMITIVE_TAG))
(define (primitive-implement p) (cadr p))

(define (primitive.a p args)
  (apply (primitive-implement p) args))

(define INPUT_PROMPT "INPUT:")
(define OUTPUT_PROMPT "OUTPUT:")

(define (drive-loop)
  (printl INPUT_PROMPT)
  (let ((input (read)))
    (let ((output (eval input GLOBAL_ENV)))
      (printl OUTPUT_PROMPT)
      (printu output)))
  (drive-loop))

(define (printl s) (display s) (newline))

(define (printu obj)
  (if (compound-proc? obj)
      (display (list COMPOUND_TAG
                     (proc-paras obj)
                     (proc-body obj)
                     '<procedure-env>))
      (display obj)))