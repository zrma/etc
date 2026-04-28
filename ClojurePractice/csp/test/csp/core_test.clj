(ns csp.core-test
  (:require [clojure.test :refer :all]
            [csp.core :refer :all]))

(deftest func-test
  (testing "func prints the greeting target"
    (is (= "Hello, Tester\n" (with-out-str (func "Tester"))))))
