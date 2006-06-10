CFLAGS=-Wall -pedantic -ansi $(shell sdl-config --cflags) -DLINUX
DEPS=./bin/video.o ./bin/main.o
SDL=$(shell sdl-config --libs) -lSDL_image

all: clean video main
	gcc $(CFLAGS) $(DEPS) -o ./bin/main $(SDL)
	chmod u+x ./bin/main
	rm -f ./main
	ln -s ./bin/main ./main
video:
	gcc $(CFLAGS) -I ./inc -c ./src/video.c -o ./bin/video.o
main:
	gcc $(CFLAGS) -I ./inc -c ./src/main.c -o ./bin/main.o
clean:
	rm -f ./main
	rm -f ./bin/main
	rm -f $(DEPS)
