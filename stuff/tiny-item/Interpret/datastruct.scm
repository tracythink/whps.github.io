(define (true? x) (not (eq? x #f)))
(define (false? x) (eq? x #f))

(define (Procedure paras body env)
  (list PROC_TAG paras body env))
  ; (list PROC_TAG paras (defs.cl body) env)) ;;; if need indefs in no-anal version
(define (compound-proc? p) (tag? p PROC_TAG))
(define (proc-paras p) (cadr p))
(define (proc-body p) (caddr p))
(define (proc-env p) (cadddr p))

(define (enclose env) (cdr env))
(define (first-frame env) 
  (if (null? env) 'EMPTY_ENV
      (first env)))
(define EMPTY_ENV '())
(define (Frame vars vals) (cons vars vals))
(define (frame-vars f) (car f))
(define (frame-vals f) (cdr f))
(define (frame.add! var val f)
  (set-car! f (cons var (frame-vars f)))
  (set-cdr! f (cons val (frame-vals f))))
(define (env.extend vars vals base-env)
  (if (= (length vars) (length vals))
      (cons (Frame vars vals) base-env)
      (error "env.extend---Unmatched vars and vals" "")))

(define (frame.lookup var f)
  (define (scan vars vals)
    (cond ((null? vars) (cons #f '()))
	  ((eq? var (car vars)) (cons #t (car vals)))
	  (else (scan (cdr vars) (cdr vals)))))
  (scan (frame-vars f) (frame-vals f)))

(define (frame.set! var val f)
  (define (scan vars vals)
    (cond ((null? vars) #f)
	  ((eq? var (car vars)) (set-car! vals val) #t)
	  (else (scan (cdr vars) (cdr vals)))))
  (scan (frame-vars f) (frame-vals f)))

(define (lookup var env)
  (if (eq? env EMPTY_ENV) (error "lookup---Unbound variable" "")
      (let ((resl (frame.lookup var (first-frame env))))
        (if (car resl) 
            (if (eq? UNASSIGN (cdr resl)) 
                (error "ilegal unassigned varibale!" "")
                (cdr resl))
            (lookup var (enclose env))))))

(define (setvar! var val env)
  (if (eq? env EMPTY_ENV) 
      (error "setvar!---Unbound variable" "")
      (if (frame.set! var val (first-frame env)) 
          'setvar-done 
          (setvar! var val (enclose env)))))


(define (defvar! var val env)
  (define f (first-frame env))
  (define (scan vars vals)
    (cond ((null? vars) (frame.add! var val f))
          ((eq? var (car vars)) (set-car! vals val))
          (else (scan (cdr vars) (cdr vals)))))
  (scan (frame-vars f) (frame-vals f)))


