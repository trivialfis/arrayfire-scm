(define-module (arrayfire array)
  #:use-module (oop goops)
  #:use-module (ice-9 optargs)
  #:use-module (arrayfire library)
  #:export (<Array>
	    make-Array
	    display))


(define-class <Array> ()
  (data #:getter get-data
	#:init-keyword #:data)
  #:name "Array")

;; other value dims dtype
(define-method (make-Array . args)
  (let-keywords
   args #f ((value #f)
	    (dims  #f)
	    (dtype #f))
   (cond (value
	  (cond ((array? value)
		 (make <Array> #:data (af-from-array value)))

		((list? value)
		 (make <Array> #:data (af-from-array
				       (list->typed-array
					dtype (array-rank value) value))))

		((is-a? value <real>)
		 (unless (and dims dtype)
		   (error "Please specify dims and dtype."))
		 (make <Array> #:data (af-constant value (length dims) dims dtype)))

		((is-a? value <Array>)
		 (make <Array> #:data (af-retain-array value)))

		;; (else (error "Don't know how to initialize Array from value."))
		))
	 (else (error "Don't know how to initialize Array.")))))

(define-generic display)
(define-method (dispaly (value <Array>))
  (print-array (get-data value)))
