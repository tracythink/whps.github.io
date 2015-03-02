(define (defs.cl body) 
  (define (name-unassigned defines) 
    (map (lambda (x) (list (def-var x) UNASSIGN)) defines)) 
  (define (set-values defines) 
    (map (lambda (x)  
           (list ASSIGN_TAG (def-var x) (def-val x)))  defines))
  (define (defines->let exprs defines not-defines) 
    (cond ((null? exprs)  
           (if (null? defines) 
               body 
               (list (list LET_TAG 
                           (name-unassigned defines)  
                           (Begin (append (set-values defines)  
                                          (reverse not-defines))))))) 
          ((def? (car exprs)) ; find all internal def and List them
           (defines->let (cdr exprs) (cons (car exprs) defines) not-defines)) 
          (else (defines->let (cdr exprs) defines (cons (car exprs) not-defines))))) 
  (defines->let body '() '()))