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

#include "fitxerWendy.h"
#include "trama.h"

#define MeSG_SERVER_INIT     "Starting Wendy...\n\n"
#define MeSG_WAIT_CONN       "Waiting new connections...\n"
#define MeSG_NEW_CONN        "[Conexion establecida]\n"

int launch_server(DadesWendy dades, int *socket_fd);
void server_run(int *server_socket, int *fd_client);

#endif