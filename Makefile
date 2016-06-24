############################# Makefile ##########################
all:
	gcc -c obj.c -lGL -lglut -lGLU -Wall -ansi -ggdb
	gcc -o main obj.o -lGL -lglut -lGLU -Wall -ansi -ggdb

clean:
	rm -rf *.o

run:
	./main

clean-all: clean
	rm -rf main
