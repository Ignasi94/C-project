all: Practica.exe

jack.o: jack.c
	gcc -Wall -Wextra -pthread -c jack.c

fitxerJack.o: fitxerJack.c fitxerJack.h
	gcc -Wall -Wextra -c fitxerJack.c
	
lloyd.o: lloyd.c lloyd.h
	gcc -Wall -Wextra -c lloyd.c
	
connexio.o: connexio.c connexio.h
	gcc -Wall -Wextra -c connexio.c
	
trama.o: trama.c trama.h
	gcc -Wall -Wextra -c trama.c
	
hallorann.o: hallorann.c hallorann.h
	gcc -Wall -Wextra -c hallorann.c
	

Practica.exe: jack.o fitxerJack.o lloyd.o connexio.o trama.o hallorann.o
	gcc jack.o fitxerJack.o lloyd.o connexio.o trama.o hallorann.o -Wall -Wextra -pthread -o S0.exe

clean:
	rm -rf *.o jack.exe
