#!/usr/bin/env guile!#

(define-module (arrayfire ling)
  #:use-module (srfi srfi-1)
  #:use-module (ice-9 format)
  #:use-module (oop goops)
  #:use-module (arrayfire array)
  #:use-module (arrayfire library)
  #:export (dot
	    matmul
	    inverse
	    transpose))

(define-generic dot)
(define-generic matmul)
(define-generic inverse)
(define-generic transpose)

(define-method (dot (x <Array>) (y <Array>))
  (let ((x-dims (af-get-dims (get-data x)))
	(y-dims (af-get-dims (get-data y)))
	(x-data (get-data x))
	(y-data (get-data y)))
    (when (or (not (equal? (cdr x-dims) '(1 1 1)))
	      (not (equal? (cdr y-dims) '(1 1 1))))
      (throw 'wrong-type-arg "dot applies only to 1D array, aka. vector."))
    (when (or (not (af-floating-p x-data))
	      (not (af-floating-p y-data)))
      (throw 'wrong-type-arg
	     "dot applies only to array with floating point values."))
    (af-dot x-data y-data)))


(define-method (matmul (x <Array>) (y <Array>))
  (let ((x-dims (af-get-dims (get-data x)))
	(y-dims (af-get-dims (get-data y)))
	(x-data (get-data x))
	(y-data (get-data y)))
    (if (and (equal? (cdr x-dims) '(1 1 1))
	       (equal? (cdr y-dims) '(1 1 1)))
	(dot x y)
	(af-matmul x-data y-data))))


(define-method (inverse (x <Array>))
  (let ((x-data (get-data x)))
    (af-inverse x-data)))

(define-method (transpose (x <Array>))
  (let ((x-data (get-data x)))
    (af-transpose x-data)))
