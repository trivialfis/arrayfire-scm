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
	
	(af-catch (lambda _ (af-matmul x-data y-data))))))


(define-method (inverse (x <Array>))
  (let ((x-data (get-data x)))
    (af-catch
     (lambda _ (af-inverse x-data)))))


(define-method (transpose (x <Array>))
  (let ((x-data (get-data x)))
    (af-catch
     (lambda _ (af-transpose x-data)))))
