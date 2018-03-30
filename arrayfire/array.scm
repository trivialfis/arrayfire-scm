;;; Initialize arrayfire-scm.
;;; Copyright © 2018 Fis Trivial <ybbs.daans@hotmail.com>
;;;
;;; This file is part of arrayfire-scm.
;;;
;;; arrayfire-scm is free software: you can redistribute it and/or modify
;;; it under the terms of the GNU General Public License as published by
;;; the Free Software Foundation, either version 3 of the License, or
;;; (at your option) any later version.
;;;
;;; arrayfire-scm is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with arrayfire-scm.  If not, see <http://www.gnu.org/licenses/>.

(define-module (arrayfire array)
  #:use-module (oop goops)
  #:use-module (ice-9 optargs)
  #:use-module (arrayfire library)
  #:export (<Array>
	    make-Array
	    get-data
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
