package util

import (
	"errors"
)

func ExampleCheckError() {
	CheckError(nil)
	// Output:
	//

	CheckError(errors.New("test"))
	// Output:
	// test
}
