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
  #:export (randu
	    dot
	    matmul
	    transpose))

(load-extension "libarrayfire-scm" "arrayfire_scm_init")

(let ((a (randu 2 '(3 3) 'f32)))
  (print-array a))

(let* ((a #u32(1 2 3))
       (b (from-array a))
       (c (from-array #u32(3 2 1))))
  (print-array b)
  (print-array c))
