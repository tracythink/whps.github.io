(define GC_TEXT
'
(begingc
   (assign free (const 0))
   (assign scan (const 0))
   (assign old (reg root))
   (assign continue (label reassign-root))
   (goto (label relocate))
 reassign-root
   (assign root (reg new))
   (goto (label gcloop))
 gcloop
   (test (op =) (reg scan) (reg free))
   (branch (label gcflip))
   (assign old (op vref) (reg newcars) (reg scan))
   (assign continue (label update-car))
   (goto (label relocate))
 update-car
   (perform (op vset) (reg newcars) (reg scan) (reg new))
   (assign old (op vref ) (reg newcdrs) (reg scan))
   (assign continue (label update-cdr))
   (goto (label relocate))
 updat-cdr
   (perform (op vset) (reg newcdrs) (reg scan) (reg new))
   (assign scan (op +) (reg scan) (const 1))
   (goto (label gcloop))
 relocate
   (test (op p2pair?) (reg old))
   (branch (label pair))
   (assign new (reg old))
   (goto (reg continue))
 pair
   (assign _old (op vref) (reg cars) (reg old))
   (test (op broken-heart?) (reg _old))
   (branch (label moved))
   (assign new (reg free))
   (assign free (op +) (reg free) (const 1))
   (perform (op vset) (reg newcars) (reg new) (reg _old))
   (assign _old (op vref) (reg cdrs) (reg old))
   (perform (op vset) (reg newcdrs) (reg new) (reg _old))
   (perform (op vset) (reg cars) (reg old) (const broken-heart))
   (perform (op vset) (reg cdrs) (reg old) (reg new))
   (goto (reg continue))
 moved
   (assign new (op vref) (reg cdrs) (reg old))
   (goto (reg continue))
 gcflip
   (assign t (reg cdrs))
   (assign cdrs (reg newcdrs))
   (assign newcdrs (reg t))
   (assign t (reg cars))
   (assign cars (reg newcars))
   (assign newcars (reg t))))

(define GC_REGS '(root cars cdrs newcars newcdrs free scan