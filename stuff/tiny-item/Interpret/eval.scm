
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
        ((apply? expr) (_apply (_eval (operator expr) env) ;;; low effect
                               (vals-list (operands expr) env)))
        (else (error "_eval---Unknown Expression Type!" ""))))

; (define eval _eval) ;;; no sperate semant and real-eval, low effect
(define eval  (λ (expr env) ((analyze expr) env)))

(define (vals-list exps env)
  (if (no? exps) '()
      (cons (eval (first exps) env)
	    (vals-list (rest exps) env))))

(define (if.e expr env)
  (if (true? (eval (if-predicate expr) env))
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
