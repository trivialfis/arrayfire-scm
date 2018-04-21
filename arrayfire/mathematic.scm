(define-module (arrayfire mathematic)
  #:use-module (arrayfire)
  #:use-module (arrayfire array)
  #:use-module (arrayfire library)
  #:use-module (ice-9 optargs)
  #:export (and
	    bitand
	    bitor
	    bitxor
	    eq
	    ge
	    gt
	    le
	    lt
	    neq
	    not))


(define-generic and)
(define-generic bitand)
(define-generic bitor)
(define-generic bitxor)
(define-generic eq)
(define-generic ge)
(define-generic gt)
(define-generic le)
(define-generic lt)
(define-generic neq)
(define-generic not)


(define-method (and (lhs <Array>) (rhs <Array>) . batch?)
  (let ((l-data (get-data lhs))
	(r-data (get-data rhs)))
    (let-optional
     batch?
     ((batch-p #f))
     (af-catch
      (lambda _ (make-Array #:value (af-and l-data r-data)))))))
