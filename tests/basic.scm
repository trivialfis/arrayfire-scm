#!/usr/bin/env guile!#

(let ((cwd (getcwd)))
  (set! %load-path (cons cwd %load-path)))

(use-modules (srfi srfi-64)
	     (arrayfire))

(test-begin "basic-test")

(test-assert "from-array:vec" (from-array #u32(1 2 4)))
(test-assert "from-array:mat" (from-array #2f32((1 2) (4 5) (7 9))))
(test-assert "print-array" (print-array (from-array #s16(1 2 3))))
(test-assert "randu" (randu 2 '(3 3) 'f32))

(test-end "basic-test")
