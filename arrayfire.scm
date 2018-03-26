(define-module (arrayfire)
  #:export (randu))

(load-extension "libarrayfire-scm" "arrayfire_scm_init")
(display (randu 2 '(2 2) 'f32))
(display "\n")
(dot (randu 2 '(2 2) 'f32) (randu 2 '(2 2) 'f32))

