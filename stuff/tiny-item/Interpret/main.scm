#lang scheme

(require rnrs/base-6) 
(require rnrs/mutable-pairs-6)

(include "settings.scm")
(include "expression.scm")
(include "datastruct.scm")
(include "init.scm")
(include "eval.scm")
(include "apply.scm")

(drive-loop)