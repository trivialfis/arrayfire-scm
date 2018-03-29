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
	     (arrayfire library))

(test-begin "mathematic")

(let ((a (af-from-array #2f32((1 2) (3 4))))
      (b (af-from-array #2u16((1 2) (3 4)))))
  (test-assert (afand a a))
  (test-assert (afbitand b b))
  (test-assert (afbitor b b))
  (test-assert (afbitxor b b))
  (test-assert (afeq a a))
  (test-assert (afge a a))
  (test-assert (afgt a a))
  (test-assert (afle a a))
  (test-assert (aflt a a))
  (test-assert (afneq a a))
  (test-assert (afnot a)))

(test-end "mathematic")
