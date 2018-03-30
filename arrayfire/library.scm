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

	    AF-ERROR-CODE
	    ))

(load-extension "libafs" "arrayfire_scm_init")

(define backend-strings '("cpu" "cuda" "opencl" "unified"))


(define AF-ERROR-CODE
  '((0   . 'AF_SUCCESS)
    (101 . 'AF_ERR_NO_MEM)
    (102 . 'AF_ERR_RUN_TIME)
    (103 . 'AF_ERR_RUNTIME)
    (201 . 'AF_ERR_INVALID_ARRAY)
    (202 . 'AF_ERR_ARG)
    (203 . 'AF_ERR_SIZE)
    (204 . 'AF_ERR_TYPE)
    (205 . 'AF_ERR_DIFF_TYPE)
    (207 . 'AF_ERR_BATCH)
    (208 . 'AF_ERR_DEVICE)
    (301 . 'AF_ERR_NOT_SUPPORTED)
    (302 . 'AF_ERR_NOT_CONFIGURED)
    (303 . 'AF_ERR_NONFREE)
    (401 . 'AF_ERR_NO_DBL)
    (402 . 'AF_ERR_NO_GFX)
    (501 . 'AF_ERR_LOAD_LIB)
    (502 . 'AF_ERR_LOAD_SYM)
    (503 . 'AF_ERR_ARR_BKND_MISMATCH)
    (998 . 'AF_ERR_INTERNAL)
    (999 . 'AF_ERR_UNKNOWN)))


(define (backend b)
  (let ((lib "libaf"))
    (if (not (member b backend-strings))
	(error "error"))
    (if (equal? b "unified")
	(dynamic-link lib)
	(dynamic-link (string-append lib b)))))
