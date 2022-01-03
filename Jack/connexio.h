#ifndef CONNEXIO_H
#define CONNEXIO_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "fitxerJack.h"
#include "trama.h"

#define MSG_SERVER_INIT     "Starting Jack...\n\n\n"
#define MSG_WAIT_CONN       "Waiting new connections...\n"
#define MSG_NEW_CONN        "[Conexion establecida]\n"

int launch_server(DadesJack dades, int *socket_fd);
void server_run(int *server_socket, int *fd_client);

#endif