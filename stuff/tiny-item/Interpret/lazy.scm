
(define (_force obj)
  (cond  ((thunk? obj)
          (let ((_r (actual-value (thunk-exp obj) (thunk-env obj))))
            (set-car! obj EVALED)
            (set-car! (cdr obj) _r)
            (set-cdr! (cdr obj) '())
            _r))
         ((evaled? obj) (thunk-val obj))
         (else obj)))
                        
                        
(define (_delay expr env)
  (list THUNK expr env))

(define (thunk? obj) (tag? obj THUNK))
(define (thunk-exp t) (cadr t))
(define (thunk-env t) (caddr t))

(define (evaled? obj) (tag? obj EVALED))
(define (thunk-val th) (cadr th))

(define (_eval expr env)
  (cond ((self-evaluating? expr) expr)
        ((var? expr) (lookup expr env))
        ((quote? expr) (quo-text expr))
        ((assign? expr) (assign.e expr env))
        ((def? expr) (def.e expr env))
        ((if? expr) (if.e expr env))
        ((lam? expr) (Procedure (lam-paras expr) (lam-body expr) env))
        ((begin? expr) (seq.e (beg-actions expr) env))
        ((cond? expr) (_eval (cond2if expr) env))
        ((let? expr) (_eval (let2lam expr) env)) 
        ((apply? expr) (__apply (actual-value (operator expr) env)
                                (operands expr)
                                env))
        (else (error "_eval---Unknown Expression Type!" ""))))

(define eval _eval) ;;; no sperate semant and real-eval, low effect

(define (vals-list exps env)
  (if (no? exps) '()
      (cons (eval (first exps) env)
	    (vals-list (rest exps) env))))

(define (if.e expr env)
  (if (true? (actual-value (if-predicate expr) env))
      (eval (if-consequent expr) env)
      (eval (if-alternative expr) env)))

(define (assign.e expr env)
  (setvar! (assign-var expr)
           (eval (assign-val expr) env)
           env )
  'assign.e-done)

(define (def.e expr env)
  (defvar! (def-var expr)
           (eval (def-val expr) env)
           env)
  'def.e-done)