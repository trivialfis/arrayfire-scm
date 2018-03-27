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
	     (arrayfire)
	     (oop goops))

(test-begin "linear-algebra")

(let ((a (from-array #2f32((1.0 3.3) (5 11))))
      (b (from-array #f64(1 3 4)))
      (c (make <afarray> #:data (from-array #f32(1 2 3)))))
  (test-assert (inverse a))
  (test-assert (transpose a))
  (test-assert (dot b b))
  (test-assert (dot c c))
  (test-error (dot c b)))

(test-end "linear-algebra")
