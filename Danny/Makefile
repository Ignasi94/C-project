all: Practica.exe

mainDanny.o: mainDanny.c
	gcc -Wall -Wextra -pthread -c mainDanny.c

fitxerConfig.o: fitxerConfig.c fitxerConfig.h
	gcc -Wall -Wextra -c fitxerConfig.c
	
direct.o: direct.c direct.h
	gcc -Wall -Wextra -c direct.c
	
connexio.o: connexio.c connexio.h
	gcc -Wall -Wextra -c connexio.c

trama.o: trama.c trama.h
	gcc -Wall -Wextra -c trama.c


Practica.exe: mainDanny.o fitxerConfig.o direct.o connexio.o trama.o
	gcc mainDanny.o fitxerConfig.o direct.o connexio.o trama.o -Wall -Wextra -pthread -o S0.exe

clean:
	rm -rf *.o S0.exe
