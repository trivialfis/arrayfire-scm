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
	     (oop goops)
	     (arrayfire array)
	     (arrayfire library))

(define-public (test-basic)
  (test-begin "basic-test")

  (test-assert "af-from-array:vec" (af-from-array #u32(1 2 4)))
  (test-assert "af-from-array:mat" (af-from-array #2f32((1 2) (4 5) (7 9))))
  (test-assert "af-randu"          (af-randu 2 '(3 3) 'f32))
  (test-assert "print-array"    (print-array (af-from-array #s16(1 2 3))))
  (let ((ar (make <Array> #:data (af-from-array #s16(1 2 3)))))
    (test-assert "display" (display ar)) ; FIXME: How to obtain the generic method?
    )
  (test-assert "from <array>" (make-Array #:value #2f32((1 2) (3.0 4))))
  (test-assert "from <real>" (make-Array #:value 3 #:dims '(1 2) #:dtype 'f32))
  (test-error "from <real> without dims" (make-Array #:value 3))
  
  (test-end "basic-test"))

(test-basic)
