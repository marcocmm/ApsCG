############################# Makefile ##########################
all:
	gcc -c casa.c object.c glm.c glm_util.c glmimg.c glmimg_jpg.c glmimg_png.c -lGL -lglut -lGLU -Wall -ggdb -lm -ljpeg -lpng
	gcc -o main casa.o object.o glm.o glm_util.o glmimg.o glmimg_jpg.o glmimg_png.o -lGL -lglut -lGLU -Wall -ggdb -lm -ljpeg -lpng

clean:
	rm -rf *.o

run:
	./main

clean-all: clean
	rm -rf main
