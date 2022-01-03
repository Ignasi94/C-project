#ifndef DIRECT_H
#define DIRECT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include "fitxerConfig.h"
#include "trama.h"



#define NOU "\n\nTenim un nou arxiu.\n "
#define ERR_OP_DIR "\n\nNo puc obrir directori\n "
#define TIPUS_JPG "\nDe tipus JPG\n "
#define TIPUS_TXT "\n\nDe tipus TXT\n "




typedef struct{

	char nomFitx[31];
	char tipus; // t-->txt, i-->jpg
	int numf;
	
}DadesFitxer;


int consultaDir(DadesFitxer *df, int fd, DadesEstacio dades, char ty);


#endif
