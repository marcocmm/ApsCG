############################# Makefile ##########################
all:
	gcc -c main.c casa.c -lGL -lglut -lGLU -Wall -ggdb
	gcc -o main main.o casa.o -lGL -lglut -lGLU -Wall -ggdb
	
clean:
	rm -rf *.o

clean-all: clean
	rm -rf main