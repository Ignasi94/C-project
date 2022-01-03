#ifndef HALLORANN_H
#define HALLORANN_H
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

#include "trama.h"







int escriuDadesTxt(DadesMet * dadesMeteoA, int * length);



//void afegeixDadesMeteo(DadesMet dm);

//void afegeixDadesMeteo(DadesMet dm);

#endif
