(define-module (arrayfire statistics)
  #:use-module (arrayfire)
  #:use-module (arrayfire array)
  #:use-module (arrayfire library)
  #:use-module (oop goops)
  #:export (mean))

(define-generic mean)

(define-method (mean (x <Array>) (dim <real>))
  (let ((x-data (get-data x)))
    (af-catch
     (lambda _ (af-mean x-data dim)))))
