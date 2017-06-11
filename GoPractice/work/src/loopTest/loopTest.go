package main

import "fmt"

func main() {
	var total int32

	for i := 0; i < 10000000; i++ {
		if i%2 == 0 {
			total++
		}
	}

	fmt.Println(" total : ", total)
}
