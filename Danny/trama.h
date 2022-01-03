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
#include <dirent.h>


#include "fitxerConfig.h"
#include "connexio.h"


#define NOU "\n\nTenim un nou arxiu.\n "
#define ERR_OP_DIR "\n\nNo puc obrir directori\n "
#define TIPUS_JPG "\nDe tipus JPG\n "
#define TIPUS_TXT "\n\nDe tipus TXT\n "



typedef struct{
  char origen[14];
  char type;
  char data[100];
}Trama;




Trama prepararTramaFImatge(char type, char dades[100]);

int EnviarTrama(int fd, Trama tramaEnviar);
/*
tipo 1 -> estableix connexió
*/
Trama prepararTramaEstacio(char type, DadesEstacio dadesEst);
/*Trama ompleTrama(int tipus, DadesTelescopi dTel);

*/
Trama prepararTrama(char type, char *dades);

Trama rebTrama(int fd);

#endif
