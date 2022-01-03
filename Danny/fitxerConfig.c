#include "fitxerConfig.h"


char *auxString;

int obtDades(DadesEstacio *dades, char nomF[20], int fd){

	int count = 0;
    long res = -1;
    char aux_char = '\0', aux_temps[20], aux_port[20];

    fd = open(nomF, O_RDONLY);
    if (fd <= 0) return 0;


	dades->nomEst = NULL;
	dades->nomEst = malloc(sizeof(char));

	res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
		dades->nomEst[count] = aux_char;
		dades->nomEst = realloc(dades->nomEst, (count+1)*sizeof(char));
		res = read(fd, &aux_char, 1);
		count++;
    }
	dades->nomEst[count - 1] = '\0';
	
	
	dades->nomCarpeta = NULL;
	dades->nomCarpeta = malloc(sizeof(char));

	res = read(fd, &aux_char, 1);
	count = 0;
    while (aux_char != '\n') {
		dades->nomCarpeta[count] = aux_char;
		dades->nomCarpeta = realloc(dades->nomCarpeta, (count+1)*sizeof(char));
		res = read(fd, &aux_char, 1);
		count++;
    }
	dades->nomCarpeta[count - 1] = '\0';
	

    count = 0;
	res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        aux_temps[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }
	dades->temps = atoi(aux_temps);

	
	
	dades->ipJack = NULL;
	dades->ipJack = malloc(sizeof(char));
    count = 0;
    res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        dades->ipJack[count] = aux_char;
		dades->ipJack = realloc(dades->ipJack, (count+1)*sizeof(char));
        res = read(fd, &aux_char, 1);
		
        count++;
    }
	dades->ipJack[count]='\0';

	count = 0;
    res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        aux_port[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }

    dades->portJack = atoi(aux_port);
	
	
	dades->ipWendy = NULL;
	dades->ipWendy = malloc(sizeof(char));
    count = 0;
    res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        dades->ipWendy[count] = aux_char;
		dades->ipWendy = realloc(dades->ipWendy, (count+1)*sizeof(char));
        res = read(fd, &aux_char, 1);
		
        count++;
    }
	dades->ipWendy[count]='\0';
	
	
	
	
	count = 0;
    res = read(fd, &aux_char, 1);
    while (res != 0) {
        aux_port[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }

    dades->portWendy = atoi(aux_port);
	
	
	
	
	
	close (fd);
	
	/*printf("Nom Est: %s.\n", dades->nomEst);
	printf("Nom Carpeta: %s.\n", dades->nomCarpeta);
	printf("Time: %d.\n",dades->temps);
		
	printf("ip Jack: %s.\n",dades->ipJack);
	printf("port Jack: %d.\n",dades->portJack);
	printf("ip wendy: %s.\n",dades->ipWendy);
	printf("port wendy: %d.\n",dades->portWendy);*/

	


  return 1;
}


