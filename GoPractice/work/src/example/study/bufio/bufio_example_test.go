package bufio

func ExampleScan() {
	Scan()
	// Output:
	// 1234
	// 5678
	// strconv.ParseInt: parsing "1234567901234567890": value out of range
	// strconv.ParseInt: parsing "1234567901234567890": value out of range
}