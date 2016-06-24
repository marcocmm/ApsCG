############################# Makefile ##########################
all:
	gcc -c casa.c object.c -lGL -lglut -lGLU -Wall -ggdb
	gcc -o main casa.o object.o -lGL -lglut -lGLU -Wall -ggdb

clean:
	rm -rf *.o

run:
	./main

clean-all: clean
	rm -rf main
