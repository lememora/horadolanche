CFLAGS=-Wall -pedantic -ansi -DLINUX
DEPS=./tmp/inimigo.o ./tmp/main.o
BIN=test-inimigo

all: inimigo main
	gcc $(CFLAGS) $(DEPS) -o ./bin/$(BIN)
	chmod u+x ./bin/$(BIN)
	rm -f ./$(BIN)
	ln -s ./bin/$(BIN) ./$(BIN)
	# =============================================
	# testes do módulo inimigo - fase 3
	# =============================================
	#
	# para executar, digite:
	# $ ./test-inimigo
	#
inimigo:
	gcc $(CFLAGS) -I ./inc -c ./src/inimigo.c -o ./tmp/inimigo.o
main:
	gcc $(CFLAGS) -I ./inc -c ./src/main.c -o ./tmp/main.o
clean:
	rm -f ./$(BIN)
	rm -f ./bin/$(BIN)
	rm -f $(DEPS)
