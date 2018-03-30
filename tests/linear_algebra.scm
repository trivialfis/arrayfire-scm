#!/usr/bin/env guile!#
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

(let ((cwd (getcwd)))
  (set! %load-path (cons cwd %load-path)))

(use-modules (srfi srfi-64)
	     (arrayfire array)
	     (arrayfire library)
	     (arrayfire ling)
	     (oop goops))

(test-begin "linear-algebra")

(let ((a (af-from-array #2f32((1.0 3.3) (5 11))))
      (b (af-from-array #f64(1 3 4)))
      (c (make <Array> #:data (af-from-array #f32(1 2))))
      (d (make-Array #:value #2f64((1 2) (4 5)))))
  (test-assert (af-inverse a))
  (test-assert (af-transpose a))
  (test-assert (af-dot b b))
  (test-error (af-dot c c))
  (test-error (af-dot c b))
  (test-assert (dot c c))
  (test-assert "matmul vector" (matmul c c))
  (test-assert "matmul matrix"
    (let ((mat (make-Array #:value #2f64((1 2) (4 5)))))
      (matmul mat mat)))
  (test-error "matmul mismatch" (matmul d c)))
  

(test-end "linear-algebra")
