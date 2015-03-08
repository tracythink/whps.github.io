#lang scheme

(require r5rs)
; (require rnrs/base-6)
; (require rnrs/mutable-pairs-6)


(include "settings.scm")
(include "machine.scm")
(include "assem.scm")

(define text '(test-b
                 (test (op =) (reg b) (const 0))
                 (branch (label donehappy))
                 (assign t (op rem) (reg a) (reg b))
                 (assign a (reg b))
                 (assign b (reg t))
                 (goto (label test-b))
               donehappy))
(define _text '(beg
                  (assign continue (label fact-done))
                fact-loop
                  (test (op =) (reg n) (const 1))
                  (branch (label base-case))
                  (save continue)
                  (save n)
                  (assign n (op -) (reg n) (const 1))
                  (assign continue (label after-fact))
                  (goto (label fact-loop))
                after-fact
                  (restore n)
                  (restore continue)
                  (assign val (op *) (reg n) (reg val))
                  (goto (reg continue))
                base-case
                  (assign val (const 1))
                  (goto (reg continue))
                fact-done))
(define _ops_ (list (list '= =) (list '- -) (list '* *)))
(define regnames '(continue val n))
(define fact (Machine regnames _ops_ _text))
(set-reg-content fact 'n 4)
(start fact)
(get-reg-content fact 'val)
(define __ops (list (list 'rem remainder) (list '= =)))
(define gcd-machine (Machine '(a b t) __ops text))
                     
(set-reg-content gcd-machine 'a 15)
(set-reg-content gcd-machine 'b 5)
; (start gcd-machine)
; (get-reg-content gcd-machine 'a)