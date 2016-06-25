############################# Makefile ##########################
all:
	gcc -c casa.c object.c glm.c glm_util.c glmimg.c -lGL -lglut -lGLU -Wall -ggdb -lm
	gcc -o main object.o casa.o glm.o glm_util.o glmimg.o -lGL -lglut -lGLU -Wall -ggdb -lm

clean:
	rm -rf *.o

run:
	./main

clean-all: clean
	rm -rf main
