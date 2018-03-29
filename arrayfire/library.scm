#!/usr/bin/env guile!#
(let ((cwd (getcwd)))
  (set! %load-path (cons cwd %load-path)))

(define-module (arrayfire library)
  #:use-module (oop goops)
  #:use-module (srfi srfi-1)
  #:use-module (ice-9 format)
  #:use-module (system foreign)
  #:export (print-array
	    af-randu
	    af-from-array

	    af-get-dims
	    af-floating-p

	    lookup
	    index
	    index-gen
	    seq-from-list

	    mean

	    afand
	    afbitand
	    afbitor
	    afbitxor
	    afeq
	    afge
	    afgt
	    afle
	    aflt
	    afneq
	    afnot

	    dot
	    matmul
	    transpose
	    inverse

	    load-image
	    save-image
	    save-array

	    af-info
	    af-init

	    <Array>
	    display
	    ))

(load-extension "libarrayfire-scm" "arrayfire_scm_init")


(define-class <Array> ()
  (data #:getter get-data
	#:init-keyword #:data)
  #:name "Array")

(define-generic display)
(define-method (dispaly (value <Array>))
  (print-array (get-data value)))

(define backend-strings '("cpu" "cuda" "opencl" "unified"))

(define (backend b)
  (let ((lib "libaf"))
    (if (not (member b backend-strings))
	(error "error"))
    (if (equal? b "unified")
	(dynamic-link lib)
	(dynamic-link (string-append lib b)))))