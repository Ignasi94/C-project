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

#include "fitxerWendy.h"
#include "connexio.h"
#include "trama.h"



typedef struct{
  char origen[14];
  char type;
  char data[100];
}Trama;



typedef struct {
	pid_t pid_tr;
	unsigned int counter;
	float temp;
	float humitat;
	float pressio;
	float precip;
}DadesMet;

typedef struct {
	char * nomIm;
	long long midaIm;
	char * md5sumIm;
}DadesImatge;




//#define _OPEN_SYS_ITOA_EXT



int prepararIEnviarTrama(int fd);
int EnviarTrama(int fd, Trama tramaEnviar);
Trama creaTramaInicial(Trama tramaIn);

DadesImatge rebTramaInicialImatge(Trama tra);
int rebImatge(DadesImatge dadIm, int fd);
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
