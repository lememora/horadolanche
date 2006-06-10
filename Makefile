CFLAGS=-Wall -pedantic -ansi $(shell sdl-config --cflags) -DLINUX
DEPS=./tmp/entrada.o ./tmp/personagem.o ./tmp/video.o ./tmp/cenario.o ./tmp/alimento.o ./tmp/inimigo.o
DEPSMAIN=./tmp/mainAnimacao.o ./tmp/mainColisao.o ./tmp/main.o 
SDL=$(shell sdl-config --libs) -lSDL_image

all: clean video entrada personagem inimigo alimento cenario main
	gcc $(CFLAGS) $(DEPS) $(DEPSMAIN) -o ./bin/horadolanche $(SDL)
	chmod u+x ./bin/horadolanche
	rm -f ./horadolanche
	ln -s ./bin/horadolanche ./horadolanche
	# =============================================
	# Hora do Lanche - Fase 3
	# =============================================
	#
	# para executar, digite:
	# $ ./horadolanche
	#
entrada:
	gcc $(CFLAGS) -I ./inc -c ./src/entrada.c -o ./tmp/entrada.o
personagem:
	gcc $(CFLAGS) -I ./inc -c ./src/personagem.c -o ./tmp/personagem.o
inimigo:
	gcc $(CFLAGS) -I ./inc -c ./src/inimigo.c -o ./tmp/inimigo.o
alimento:
	gcc $(CFLAGS) -I ./inc -c ./src/alimento.c -o ./tmp/alimento.o
video: 
	gcc $(CFLAGS) -I ./inc -c ./src/video.c -o ./tmp/video.o
cenario: 
	gcc $(CFLAGS) -I ./inc -c ./src/cenario.c -o ./tmp/cenario.o
main:
	gcc $(CFLAGS) -I ./inc -c ./src/mainAnimacao.c -o ./tmp/mainAnimacao.o
	gcc $(CFLAGS) -I ./inc -c ./src/mainColisao.c -o ./tmp/mainColisao.o
	gcc $(CFLAGS) -I ./inc -c ./src/main.c -o ./tmp/main.o
	
clean:
	rm -f ./horadolanche
	rm -f ./bin/horadolanche
	rm -f $(DEPS)
