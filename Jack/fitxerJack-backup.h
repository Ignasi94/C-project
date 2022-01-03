#include "fitxerJack.h"
#include "trama.h"


char *auxString;
DadesMet * dadesMeteo;
int length = 0;
unsigned int numDadesTotals = 0;

int obtDades(DadesJack *dades, char nomF[20], int fd){

	int count = 0;
    long res = -1;
    char aux_char = '\0', aux_temps[20], aux_port[20];

    fd = open(nomF, O_RDONLY);
    if (fd <= 0) return 0;


	dades->ip = NULL;
	dades->ip = malloc(sizeof(char));
	count = 0;
    res = read(fd, &aux_char, 1); 	
    while (aux_char != '\n') {
        dades->ip[count] = aux_char;
		dades->ip = realloc(dades->ip, (count+1)*sizeof(char));
        res = read(fd, &aux_char, 1);
        count++;
    }
	dades->ip[count]='\0';

	
	count = 0;
    res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        aux_port[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }

    dades->portMcGruder = atoi(aux_port);
	
	
	
	
	
	count = 0;
    res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        aux_port[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }

    dades->portMcTavish = atoi(aux_port);
	
	
	
	
	
	
	count = 0;
	res = read(fd, &aux_char, 1);
	
    while (res != 0 && aux_char != '\n') {
        aux_temps[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }
	
	dades->temps = atoi(aux_temps);
	
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


void afegeixDadesMeteo(DadesMet dm){
	numDadesTotals++;
	int index;
	
	if (numDadesTotals == 1){//Si es primer cop fem malloc
		dadesMeteo = (DadesMet *) malloc(sizeof(DadesMet));
		dadesMeteo[0] = dm;
		dadesMeteo[0].counter = 0;
		
	}else{//Si no és el primer cop, fem realloc si encara no existeix
		index = -1;
		for(int i = 0; i < ((sizeof(dadesMeteo)/sizeof(dadesMeteo[0])) - 1); i++){
			
			if (strcp(dm.nomEst, dadesMeteo[i].nomEst) == 0){
				index = i;
				break;
			}
		}
		//Mirem si ja existeix
		if (index < 0){//Cas que no existeixi
			length++;
			//Ampliem una posició de memoria
			dadesMeteo = realloc(dadesMeteo, (length+1)*sizeof(dadesMeteo));
			dadesMeteo[length] = dm;
			dadesMeteo[length].counter = 0;
			
		}else{//Cas que ja existeixi
		
			dadesMeteo[index].counter += 1;
			//Calcular la mitja
			
			dadesMeteo[index].temp = (dadesMeteo[index].temp + dm.temp) / (dadesMeteo[index].counter);
			dadesMeteo[index].humitat = (dadesMeteo[index].humitat + dm.humitat) / (dadesMeteo[index].counter + 1);
			dadesMeteo[index].pressio = (dadesMeteo[index].pressio + dm.pressio) / (dadesMeteo[index].counter + 1);
			dadesMeteo[index].precip = (dadesMeteo[index].precip + dm.precip) / (dadesMeteo[index].counter + 1);
		}
		
	}
	
	for(int j = 0; j < (length); j++){
		printf("Name: %s\n", &dadesMeteo[j].nomEst);
		printf("temp mitja: %f\n", dadesMeteo[j].temp);
		printf("humitat mitja: %f\n", dadesMeteo[j].humitat);
		printf("pressio mitja: %f\n", dadesMeteo[j].pressio);
		printf("precip mitja: %f\n\n\n\n", dadesMeteo[j].precip);		
		
		
	}
	
	printf("Dades");
	
}


