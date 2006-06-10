CFLAGS=-Wall -pedantic -ansi -DLINUX
DEPS=./tmp/personagem.o ./tmp/main.o
BIN=test-personagem

all: personagem main
	gcc $(CFLAGS) $(DEPS) -o ./bin/$(BIN)
	chmod u+x ./bin/$(BIN)
	rm -f ./$(BIN)
	ln -s ./bin/$(BIN) ./$(BIN)
	# =============================================
	# testes do módulo personagem - fase 3
	# =============================================
	#
	# para executar, digite:
	# $ ./test-personagem -i ./var/test/entrada.txt
	#
personagem:
	gcc $(CFLAGS) -I ./inc -c ./src/personagem.c -o ./tmp/personagem.o
main:
	gcc $(CFLAGS) -I ./inc -c ./src/main.c -o ./tmp/main.o
clean:
	rm -f ./$(BIN)
	rm -f ./bin/$(BIN)
	rm -f $(DEPS)
