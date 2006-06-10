CFLAGS=-Wall -pedantic -ansi -O2 -DLINUX
DEPS=./bin/cenario.o ./bin/main.o

all: clean cenario main
	gcc $(CFLAGS) $(DEPS) -o ./bin/cenario
	chmod u+x ./bin/cenario
	ln -s ./bin/cenario ./testecen
	#========================================================
	#    Teste de implementacao do cenario - Fase 3
	#========================================================
	# Para executar, digite:
	# ./testecen -i var/def.txt -m var/1.txt -o var/s.txt
	#========================================================
cenario:
	gcc $(CFLAGS) -I ./inc -c ./src/cenario.c -o ./bin/cenario.o
main:
	gcc $(CFLAGS) -I ./inc -c ./src/main.c -o ./bin/main.o
clean:
	rm -f $(DEPS) ./bin/cenario ./testecen ./var/s.txt
	 
