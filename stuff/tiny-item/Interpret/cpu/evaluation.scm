
'
(eval
   (test (op self?) (reg expr))
   (branch (label evalself))
   (test (op var?) (reg expr))
   (branch (label evalvar))
   (test (op quote?) (reg expr))
   (branch (label evalquo))
   (test (op assign?) (reg expr))
   (branch (label evalassign))
   (test (op def?) (reg expr))
   (branch (label evaldef))
   (test (op if?) (reg expr))
   (branch (label evalif))
   (test (op lam?) (reg expr))
   (branch (label evallam))
   (test (op beg?) (reg expr))
   (branch (label evalbeg))
   (test (io apply?) (reg expr))
   (branch (label evalapply))
   (goto (label badexpr))
 evalself
   (assign val (reg val))
   (goto (reg continue))
 evalvar
   (assign val (op lookup) (reg expr) (reg env))
   (goto (reg continue))
 evalquo
   (assign val (op text) (reg expr))
   (goto (reg continue))
 evallam
   (assign uenv (op lamparas) (reg expr))
   (assign expr (op lambody) (reg expr))
   (assign val (op Procedure) (reg uenv) (reg expr) (reg env))
   (goto (reg continue))
 evalapply
   (save continue)
   (save env)
   (assign uenv (op operands) (reg expr))
   (save uenv)
   (assign expr (op operator) (reg expr))
   (assign continue (label aftereval))
   (goto (label eval))
 aftereval
   (restore uenv)
   (restore env)
   (assign argl (op emptyargs))
   (assign proc (reg val))
   (test (op nooprands?) (reg uenv))
   (branch (label apply))
   (save proc)
 evalargs
   (save argl)
   (assign expr (op first) (reg uenv))
   (test (op last?) (reg uenv))
   (branch (label lastarg))
   (save env)
   (save uenv)
   (assign continue (label accuarg))
   (goto (label eval))
 accuarg
   (restore uenv)
   (restore env)
   (restore argl)
   (assign argl (op join) (reg val) (reg argl))
   (assign uenv (op rest) (reg uenv))
   (goto (label evalargs))
 lastarg
   (assign continue (label accuarg))
   (goto (label eval))
 apply
   (test (op prim?) (reg proc))
   (branch (label applyprim))
   (test (op compound?) (reg proc))
   (branch (label applycompound))
 applyprim
   (assign val (op prim) (reg proc) (reg argl))
   (restore continue)
   (goto (reg continue))
 applycompound
   (assign uenv (op procparas) (reg proc))
   (assign env (op provenv) (reg proc))
   (assign env (op extendenv) (reg uenv) (reg argl) (reg env))
   (goto (label evalseq))
 evalbeg
   (assign uenv (op begactions) (reg expr))
   (save continue)
   (goto (label evalseq))
 evalseq
   (assign expr (op first) (reg uenv))
   (test (op last?) (reg uenv))
   (branch (label lastexpr))
   (save uenv)
   (save env)
   (assign continue (label seqcontinue))
   (goto (label eval))
 seqconitnue
   (restore env)
   (restore uenv)
   (assign uenv (op rest) (reg uenv))
   (goto (label evalseq))
 lastexpr
   (restore continue)
   (goto (label eval))
 evalif
   (save expr)
   (save env)
   (save continue)
   (assign continue (label decide))
   (assign expr (op predicate) (reg expr))
   (goto (label evla))
 decide 
   (restore continue)
   (restore expr)
   (restore env)
   (test (op true?) (reg val))
   (branch (label consequent))
 
   (assign expr (op alternative) (reg expr))
   (goto (label eval))
 consequent
   (assign expr (op consequent) (reg expr))
   (goto (label eval))
 evalassign
   (assign uenv (op assignvar) (reg expr))
   (save uenv)
   (assign expr (op assignval) (reg expr))
   (save env)
   (save continue)
   (assign continue (label doassign))
   (goto (label eval))
 doassign
   (restore continue)
   (restore env)
   (restore uenv)
   (perform (op setvar) (reg uenv) (reg val) (reg env))
   (goto (reg continue))
 evaldef
   (assign uenv (op defvar) (reg expr))
   (save uenv)
   (assign expr (op defval) (reg expr))
   (save env)
   (save continue)
   (assign continue (label dodef))
   (goto (label eval))
 dodef
   (restore uenv)
   (restore env)
   (restore continue)
   (perform (op defvar) (reg uenv) (reg val) (reg env))
   (goto (reg continue)))

           
   
   
          
   