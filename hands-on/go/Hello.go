package main

import "fmt"

func main(){
	var i int
	int_pointer := &i
	*int_pointer = 100
	fmt.Print("Hello world!\n")
	fmt.Printf("int_point value:%s\n", *int_pointer)
}
