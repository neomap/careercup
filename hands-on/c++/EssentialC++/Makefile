#101.a: 101.cpp
#all: $(basename $(wildcard *.a))
%.a: %.cpp
	g++ -g -o $@ $<
clean:
	rm *.a
