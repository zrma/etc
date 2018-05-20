(ns csp.core)

(use '[clojure.string :only (join split)])

(defn func
	"This is comment."
	[x]
	(println "Hello," (join "" [g])))

(defn multiple
	[]
	(doall
		(for [x (range 2 10) y (range 1 10)]
			(println (format "%d x %d = %d" x y (* x y))))))


(func "World")
;; (multiple)