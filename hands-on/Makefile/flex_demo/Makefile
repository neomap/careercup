LDFLAGS =  -L/usr/local/opt/flex/lib
count_words: count_words.o lexer.o
	gcc count_words.o lexer.o -lfl -o count_words $(LDFLAGS)

count_words.o: count_words.c
	gcc -c count_words.c

lexer.o: lexer.c
	gcc -c lexer.c

lexer.c: lexer.l
	flex -t lexer.l > lexer.c

clean: 
	rm *.o lexer.c count_words
