#include "fitxerJack.h"
#include "trama.h"


char *auxString;
/*DadesMet * dadesMeteo;
int length = 0;
unsigned int numDadesTotals = 0;*/

int obtDades(DadesJack *dades, char nomF[20], int fd){

	int count = 0;
    long res = -1;
    char aux_char = '\0', aux_port[20];

    fd = open(nomF, O_RDONLY);
    if (fd <= 0) return 0;


	/*dades->ip = NULL;
	dades->ip = (char *)malloc(sizeof(char));*/
	count = 0;
    res = read(fd, &aux_char, 1); 	
    while (aux_char != '\n') {
        dades->ip[count] = aux_char;
		//dades->ip = (char *)realloc(dades->ip, (count+1)*sizeof(char));
        res = read(fd, &aux_char, 1);
        count++;
    }
	dades->ip[count]='\0';

	
	count = 0;
    res = read(fd, &aux_char, 1);
    while (res != 0) {
        aux_port[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }

    dades->portJack = atoi(aux_port);
	
	
	
	//
	close (fd);
	
	//printf("%s\n",dades->ip);
	/*printf("ip picard: %s.\n",dades->ip);
	printf("port picard: %d.\n",dades->portMcGruder);
	printf("port picard: %d.\n",dades->portMcTavish);
	printf("size Nom: %d.\n",dades->temps);
	*///printf("Nom: %s.\n", dades->nomTel);
	
	return 1;
}






