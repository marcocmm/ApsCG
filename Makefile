############################# Makefile ##########################
all:
	gcc -c obj.c -lGL -lglut -lGLU -Wall -ggdb
	gcc -o main obj.o -lGL -lglut -lGLU -Wall -ggdb

clean:
	rm -rf *.o

run:
	./main

clean-all: clean
	rm -rf main
