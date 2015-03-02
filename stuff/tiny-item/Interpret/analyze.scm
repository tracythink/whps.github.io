(define (analyze expr)
  (cond ((self-evaluating? expr) (self.an expr))
        ((var? expr) (var.an expr))
        ((quote? expr) (quo.an expr))
        ((assign? expr) (assign.an expr))
        ((def? expr) (def.an expr))
        ((if? expr) (if.an expr))
        ((lam? expr) (lam.an expr))
        ((begin? expr) (seq.an (beg-actions expr)))
        ((cond? expr) (analyze (cond2if expr)))
        ((let? expr) (analyze (let2lam expr))) ;;; TODO => evaln unimplement
        ((apply? expr) (apply.an expr))
        (else (error "analyze---Unknown Expression Type!" ""))))

(define (self.an expr) (lambda (e) expr))

(define (quo.an expr)
  (let ((qval (quo-text expr)))
    (lambda (e) qval)))

(define (var.an expr) (lambda (e)  (lookup expr e)))

(define (assign.an expr)
  (let ((var (assign-var expr))
        (vproc (analyze (assign-val expr))))
    (lambda (e) (setvar! var (vproc e) e))))

(define (def.an expr)
  (let ((var (def-var expr))
        (vproc (analyze (def-val expr))))
    (lambda (e) (defvar! var (vproc e) e))))

(define (if.an expr)
  (let ((pproc (analyze (if-predicate expr)))
        (cproc (analyze (if-consequent expr)))
        (aproc (analyze (if-alternative expr))))
    (lambda (e) (if (true? (pproc e))
                    (cproc e)
                    (aproc e)))))

(define (lam.an expr)
  (let ((vars (lam-paras expr))
        (bproc (seq.an (lam-body expr))))
    (lambda (e) (Procedure vars bproc e))))

(define (seq.an exps)
  (define (magic p1 p2) (lambda (e) (p1 e) (p2 e)))
  (define (loop _resl _rest)
    (if (null? _rest) _resl
        (loop (magic _resl (car _rest)) (cdr _rest))))
  (let ((procs (map analyze exps)))
    (if (null? procs) 
        (error "analyze---Empty sequence!" "")
        (loop (car procs) (cdr procs)))))

(define (apply.an expr)
  (let ((fproc (analyze (operator expr)))
        (argsproc (map analyze (operands expr))))
    (lambda (e) (exec (fproc e)
                      (map (lambda (p) (p e)) argsproc)))))

(define (exec proc args)
  (cond ((primitive-proc? proc) (primitive.a proc args))
        ((compound-proc? proc) ((proc-body proc)
                                (env.extend (proc-paras proc) args (proc-env proc))))
        (else (error "exec---unknown procedure type" ""))))
         
