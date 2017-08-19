package main

import "runtime"
import "fmt"

func main() {
	nCpu := runtime.NumCPU()
	fmt.Println("Num Of CPUs =", nCpu)

	// 동시에 사용할 cpu 설정
	nPreviousSetting := runtime.GOMAXPROCS(nCpu)

	fmt.Println("Previous gomaxprocs =", nPreviousSetting)

	var i int

	go func() {
		for {
			i++
		}
	}()

	go func() {
		for {
			i++
		}
	}()

	go func() {
		for {
			i++
		}
	}()

	go func() {
		for {
			i++
		}
	}()

	fmt.Println("Num Of go routine =", runtime.NumGoroutine())

	input := ""
	fmt.Scanln(&input)
}
