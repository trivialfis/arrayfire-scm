#!/usr/bin/env guile!#
(let ((cwd (getcwd)))
  (set! %load-path (cons cwd %load-path)))

(use-modules (srfi srfi-1)
	     (ice-9 format)
	     (system foreign)
	     (arrayfire))

(define backend-strings '("cpu" "cuda" "opencl" "unified"))

;; (define-wrapped-pointer-type af-c-array
;;   af-c-array?
;;   wrap-af-c-array unwrap-af-c-array
;;   (lambda (b p)
;;     (format p "#<af-c-array of ~a ~x>"
;;             (af-c-array-contents b)
;;             (pointer-address (unwrap-af-c-array b)))))

(define (backend b)
  (let ((lib "libaf"))
    (if (not (member b backend-strings))
	(error "error"))
    (if (equal? b "unified")
	(dynamic-link lib)
	(dynamic-link (string-append lib b)))))

;; (define* (af-array val)
;;   (lambda _
;;     val))

;; (define (bind x y fn)
;;   (lambda (back)
;;     (print-array (x))
;;     (let* ((x_val (scm->pointer (x)))
;; 	   (y_val (scm->pointer (y)))
;; 	   (proc (pointer->procedure int
;; 				     (dynamic-func fn back)
;; 				     (list '* '* '*))))
;;       (display "class-of\n")
;;       (display (class-of x_val))
;;       (display "\n")
;;       (let* ((result (create-empty-array))
;; 	     (rp (scm->pointer result)))
;; 	(proc rp x_val y_val)
;; 	(display "result")
;; 	(display "\n")
;; 	(display (class-of result))
;; 	;; (print-array (pointer->scm rp))
;; 	)
;;       (af-array (proc x_val y_val)))))

;; (define (matmul x y)
;;   (bind x y "af_matmul"))

;; (define (print x)
;;   (let* ((back (backend "cpu"))
;; 	 (value (x back))
;; 	 (disp (pointer->procedure '*
;; 				   (dynamic-func "af_print_array" back)
;; 				   '*)))
;;     (display "in print")
;;     (display (class-of value))
;;     (disp value)))
