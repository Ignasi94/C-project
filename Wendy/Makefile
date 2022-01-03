all: Practica.exe

wendy.o: wendy.c
	gcc -Wall -Wextra -pthread -c wendy.c

fitxerWendy.o: fitxerWendy.c fitxerWendy.h
	gcc -Wall -Wextra -c fitxerWendy.c
	
	
connexio.o: connexio.c connexio.h
	gcc -Wall -Wextra -c connexio.c
	
trama.o: trama.c trama.h
	gcc -Wall -Wextra -c trama.c
	

Practica.exe: wendy.o fitxerWendy.o connexio.o trama.o
	gcc wendy.o fitxerWendy.o connexio.o trama.o -Wall -Wextra -pthread -o S0.exe

clean:
	rm -rf *.o wendy.exe
