(define (_apply proc args)
  (cond ((primitive-proc? proc) (primitive.a proc args))
        ((compound-proc? proc)
         (seq.e (proc-body proc)
                (env.extend (proc-paras proc) args (proc-env proc))))
        (else (error "Unknown Procedure Type" ""))))

(define (seq.e exps env)
  (cond ((last? exps) (eval (first exps) env))
        (else (eval (first exps) env)
              (seq.e (rest exps) env))))
