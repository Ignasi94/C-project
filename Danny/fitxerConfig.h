#ifndef FITXERCONFIG_H
#define FITXERCONFIG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>



#define SORTIR_ "\n\nClose and exit\n "
#define ARG_ "Falten arguments\n"
#define COM_ "introdueixi comandes:\n"
#define EFITX_ "Error al llegir fitxer.\n"


typedef struct{

	char *nomEst;
	char *nomCarpeta;
	int temps;
	char *ipJack;
	char *ipWendy;
	int portJack;
	int portWendy;

}DadesEstacio;


void tancar_prog();
int obtDades(DadesEstacio *dades, char nomF[20], int fd);

#endif
