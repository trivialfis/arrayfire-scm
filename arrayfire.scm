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

(define-module (arrayfire)
  #:use-module (oop goops)
  #:export (print-array
	    randu
	    from-array

	    af-get-dims
	    af-floating-p

	    lookup
	    index
	    index-gen
	    seq-from-list

	    mean

	    afand
	    afbitand
	    afbitor
	    afbitxor
	    afeq
	    afge
	    afgt
	    afle
	    aflt
	    afneq
	    afnot

	    dot
	    matmul
	    transpose
	    inverse

	    load-image
	    save-image
	    save-array

	    af-info
	    af-init

	    <afarray>))

(load-extension "libarrayfire-scm" "arrayfire_scm_init")

(define-class <afarray> ()
  (data #:getter get-data
	#:init-keyword #:data)
  #:name "afarray")

(define-generic dot)

(define-method (dispaly (value <afarray>))
  (print-array (get-data value)))

(define-method (dot (x <afarray>) (y <afarray>))
  (let ((x-dims (af-get-dims (get-data x)))
	(y-dims (af-get-dims (get-data y)))
	(x-data (get-data x))
	(y-data (get-data y)))
    (display (cdr x-dims))
    (when (or (not (equal? (cdr x-dims) '(1 1 1)))
	      (not (equal? (cdr y-dims) '(1 1 1))))
      (throw 'wrong-type-arg "dot applies only to 1D array, aka. vector."))
    (when (or (not (af-floating-p x-data))
	      (not (af-floating-p y-data)))
      (throw 'wrong-type-arg
	     "dot applies only to array with floating point values."))
    (dot x-data y-data)))
