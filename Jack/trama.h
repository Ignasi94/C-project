#ifndef TRAMA_H
#define TRAMA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <strings.h>
#include <pthread.h>


//#include "dataFunc.h"
//#include "llistaOrdenada.h"

#include "fitxerJack.h"
#include "connexio.h"
#include "trama.h"



typedef struct{
  char origen[14];
  char type;
  char data[100];
}Trama;





typedef struct {
	char nomEst[31];
	unsigned int counter;
	float temp;
	float humitat;
	float pressio;
	float precip;
}DadesMet;



//#define _OPEN_SYS_ITOA_EXT


int prepararIEnviarTrama(int fd);
int EnviarTrama(int fd, Trama tramaEnviar);
Trama creaTramaInicial(Trama tramaIn);

DadesMet * EscriuADadesMet(Trama tra, char * nome);
//Trama creaTrama(char );
int esDanny(Trama tramaIn);

Trama prepararTrama(char type, char *dades);
int ompleTrama(int tipus);
int generaTxt(Trama trama, Trama tramaInfo, int numString, char ***input);
char * utoa(unsigned int value, char * str, int radix);


Trama rebTrama(int fd);
//int analitzaTrama(Trama trama);
/*int prepararIEnviarTrama(Trama trama, int fd);
Trama ompleTrama(int tipus, Enterprise enterprise);
int afegirEnterprise(LlistaOrdenada enterprises, Trama trama);
int actualitzarEnterprise(LlistaOrdenada enterprises, Trama trama);
int desconectarEnterprise(LlistaOrdenada enterprises,Trama trama);
*/
#endif
