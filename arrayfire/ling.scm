#!/usr/bin/env guile!#
(let ((cwd (getcwd)))
  (set! %load-path (cons cwd %load-path)))

(use-modules (srfi srfi-1)
	     (ice-9 format)
	     (oop goops)
	     (arrayfire))

(define-generic dot)
(define-generic matmul)

(define-method (dot (x <afarray>) (y <afarray>))
  (let ((x-dims (af-get-dims (get-data x)))
	(y-dims (af-get-dims (get-data y)))
	(x-data (get-data x))
	(y-data (get-data y)))
    ;; (display (cdr x-dims))
    (when (or (not (equal? (cdr x-dims) '(1 1 1)))
	      (not (equal? (cdr y-dims) '(1 1 1))))
      (throw 'wrong-type-arg "dot applies only to 1D array, aka. vector."))
    (when (or (not (af-floating-p x-data))
	      (not (af-floating-p y-data)))
      (throw 'wrong-type-arg
	     "dot applies only to array with floating point values."))
    (dot x-data y-data)))

(define-method (matmul (x <afarray>) (y <afarray>))
  (let ((x-data (get-data x))
	(y-data (get-data y)))
    (matmul x-data y-data)))

(define-method (inverse (x <afarray>))
  (let ((x-data (get-data x)))
    (inverse x-data)))

(define-method (transpose (x <afarray>))
  (let ((x-data (get-data x)))
    (transpose x-data)))
