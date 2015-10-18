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

### Reference
- [Managing Projects with GNU Make, Third Edition By Robert Mecklenburg][1]

[1]: http://www.oreilly.com/openbook/make3/book/index.csp