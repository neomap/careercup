### quick guide
- [A Simple Makefile Tutorial](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

### Tips
* The regular makefile rule looks like this:
```
FileToBuild: Other targets this one depends on
<tab> Commands to generate FileToBuild
```
- What is the purpose of .PHONY target?
To put it simple, .PHONY target tells `make` to know that such targets are not real files,
to avoid checking whether it is modified to skip build
> Labeling the target "clean" as "phony" will prevent that. It tells "make" that "clean" is a phony target, i.e. not a real file that needs to be kept up to date.

* CFLAGS, CPPFLAGS, CXXFLAGS

CPPFLAGS is supposed to be for flags for the C PreProcessor; CXXFLAGS is for flags for the C++ compiler.
The default rules in make (on my machine, at any rate) pass CPPFLAGS to just about everything, CFLAGS is only passed when compiling and linking C, and CXXFLAGS is only passed when compiling and linking C++.

### Examples
* To compile with c++11

```
CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
BIN=prog

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
    $(CXX) -o $(BIN) $^

%.o: %.c
    $(CXX) $@ -c $<

clean:
    rm -f *.o
    rm $(BIN)
```

### Reference
- [Managing Projects with GNU Make, Third Edition By Robert Mecklenburg][1]

[1]: http://www.oreilly.com/openbook/make3/book/index.csp