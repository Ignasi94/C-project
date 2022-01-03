#ifndef FITXERWENDY_H
#define FITXERWENDY_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#include <errno.h>

//#include "trama.h"




#define SORTIR_ "\n\nClose and exit\n "
#define EFITX_ "Error al llegir fitxer.\n"
#define ERROR_CREAR_SOCKET "Error al crear socket.\n"
#define ERROR_CREAR_SOCKET_A "Error al crear socketA.\n"
#define MSG_NEW_CONN        "[Conexion establecida]\n"
#define ERROR_BIND        "Error durante el bind del puerto.\n"
#define SERVIDOR_ON     "Starting Wendy---\n\n"
#define EFITX_ "Error al llegir fitxer.\n"

#define LISTEN_BACKLOG	64
#define FRAME_MAX	 64

typedef struct{

	char ip[20];
	int port;

}DadesWendy;


//void afegeixDadesMeteo(DadesMet dm);

//void afegeixDadesMeteo(DadesMet dm);
void tancar_prog();
int obtDades(DadesWendy *dades, char nomF[20], int fd);

#endif
