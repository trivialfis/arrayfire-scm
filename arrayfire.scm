(define-module (arrayfire)
  #:export (randu))

(load-extension "libarrayfire-scm" "init_type")
(randu 4 '(2 2) 'f32)
(print (randu 4 '(2 2) 'f32))
(display (randu 4 '(2 2) 'f32))
