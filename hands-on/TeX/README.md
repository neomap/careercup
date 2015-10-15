#TeX
Created by Donald Knuth.

* [TeX User group site](http://www.tug.org)
* Mac version [download link](http://www.tug.org/mactex/mactex-download.html). It's pretty large. You can consider just download and install basic components, following [link](http://www.tug.org/mactex/morepackages.html)
* Basic package will install TeX to /usr/local/texlive/2015basic/
* In order to play with tex, you can download its [plain text source](ftp://tug.ctan.org/pub/tex-archive/systems/knuth/dist/lib/plain.tex)

## Try to compile it?
See [How to compile source code of Tex](http://tex.stackexchange.com/questions/111332/how-to-compile-the-source-code-of-tex)

## Hello world and hands-on
1. Include tex installation path: ` export PATH=/usr/local/texlive/2015basic/bin/universal-darwin/:$PATH`
2. vim, and save the following text to hello.tex
```
The quadratic formula is $-b \pm \sqrt{b^2 - 4ac} \over 2a$ \bye 
```
3. Type command to generate pdf file for it: `pdftex hello.tex`
