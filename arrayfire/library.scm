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

(define-module (arrayfire library)
  #:use-module (oop goops)
  #:use-module (srfi srfi-1)
  #:use-module (ice-9 format)
  #:use-module (system foreign)
  #:export (print-array

	    af-randu
	    af-from-array
	    af-create-empty
	    af-retain-array
	    af-constant

	    af-get-dims af-floating-p

	    lookup    index
	    index-gen seq-from-list

	    mean

	    afand   afbitand
	    afbitor afbitxor
	    afeq    afge
	    afgt    afle
	    aflt    afneq
	    afnot

	    af-dot       af-matmul
	    af-transpose af-inverse

	    load-image save-image
	    save-array

	    af-info af-init
	    ))

(load-extension "libafs" "arrayfire_scm_init")

(define backend-strings '("cpu" "cuda" "opencl" "unified"))

(define (backend b)
  (let ((lib "libaf"))
    (if (not (member b backend-strings))
	(error "error"))
    (if (equal? b "unified")
	(dynamic-link lib)
	(dynamic-link (string-append lib b)))))
