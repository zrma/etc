package main

import (
	"fmt"
	"io"
	"net"
	"strconv"
)

// PORT - listen port
const PORT = 35555

func main() {
	// db.Init()

	server, err := net.Listen("tcp", ":"+strconv.Itoa(PORT))
	if server == nil {
		panic("couldn't start listening: " + err.Error())
	}

	conn := clientConn(server)
	for {
		go handleConn(<-conn)
	}
}

func clientConn(listener net.Listener) chan net.Conn {

	ch := make(chan net.Conn)
	i := 0

	go func() {
		for {
			client, err := listener.Accept()
			if client == nil {
				fmt.Printf("couldn't accept: " + err.Error())
				continue
			}

			i++
			fmt.Printf("%d: %v <-> %v\n", i, client.LocalAddr(), client.RemoteAddr())

			ch <- client
		}
	}()

	return ch
}

func handleConn(client net.Conn) {
	// echo
	io.Copy(client, client)
}
