(define (self-evaluating? expr)
  (cond ((number? expr) #t)
        ((string? expr) #t)
        (else #f)))

(define (var? expr) (symbol? expr))

(define (quote? expr) (tag? expr QUOTE_TAG))

(define (quo-text expr) (cadr expr))

(define (tag? expr tag)
  (if (pair? expr) (eq? (car expr) tag) #f)) 

(define (assign? expr) (tag? expr ASSIGN_TAG))
(define (assign-var expr) (cadr expr))
(define (assign-val expr) (caddr expr))

(define (def? expr) (tag? expr DEF_TAG))
(define (def-var expr)
  (if (symbol? (cadr expr)) (cadr expr) (caddr expr)))
(define (def-val expr)
  (if (symbol? (cadr expr)) (caddr expr)
      (Lam (cdadr expr) (cddr expr))))

(define (lam? expr) (tag? expr LAMBDA_TAG))
(define (lam-paras expr) (cadr expr))
(define (lam-body expr) (cddr expr))
(define (Lam paras body) (cons LAMBDA_TAG (cons paras body)))

(define (if? expr) (tag? expr IF_TAG))
(define (if-predicate expr) (cadr expr))
(define (if-consequent expr) (caddr expr))
(define (if-alternative expr) (cadddr expr)) ; must have else-part
(define (If p c a) (list IF_TAG p c a))

(define (begin? expr) (tag? expr BEGIN_TAG))
(define (beg-actions expr) (cdr expr))
(define (last? seq) (null? (cdr seq)))
(define (first seq) (car seq))
(define (rest seq) (cdr seq))

(define (seq2expr seq) 
  (cond ((null? seq) seq)
	((last? seq) (first seq))
	(else (Begin seq))))
(define (Begin seq) (cons BEGIN_TAG seq))

(define (apply? expr) (pair? expr))
(define (operator expr) (car expr))
(define (operands expr) (cdr expr))
(define (no? ops) (null? ops))

(define (cond? expr) (tag? expr COND_TAG))
(define (cond-clauses expr) (cdr expr))
(define (else-clause? clause) 
  (eq? (clause-predicate clause) COND_ELSE_TAG))
(define (clause-predicate clause) (car clause))
(define (clause-actions clause) (cdr clause))
(define (cond2if expr) (clauses.expand (cond-clauses expr)))
(define (clauses.expand clauses)
  (if (null? clauses) #f
      (let ((_first (first clauses))
            (_rest (rest clauses)))
        (if (else-clause? _first)
            (if (null? _rest) (seq2expr (clause-actions _first))
                (error "clauses.expand---ELSE clause isn't last" ""))
            (If (clause-predicate _first)
                (seq2expr (clause-actions _first))
                (clauses.expand _rest))))))

(define (let? expr) (tag? expr LET_TAG))
(define (let-vars expr) (map car (cadr expr)))
(define (let-inits expr) (map cadr (cadr expr)))
(define (let-body expr) (cddr expr))

(define (let2lam expr) 
  (cons (Lam (let-vars expr) (let-body expr)) (let-inits expr)))