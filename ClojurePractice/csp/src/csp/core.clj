(ns csp.core)

(defn foo
	"I don't do a whole lot."
	[x]
	(println x "Hello, World!"))

(defn gugu
	[]
	(doall
		(for [x (range 2 10) y (range 1 10)]
			(println (format "%d x %d = %d" x y (* x y))))))


(foo "Tester")
(gugu)