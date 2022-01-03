#include "trama.h"


Trama trama;

int fichero;
 int maxH = 15;
/*
Trama rebTrama(int fd){	

int z,x;
	char aux ;
	char auxString[20];
	x = read(fd, &aux, sizeof(char));
	while(aux != '\n'){
		x = read(fd, &aux, sizeof(char));
		sprintf(auxString, "%c\n", aux);
		write(1, auxString, strlen(auxString));
	}
}*/


///////////

///////////

///////

Trama rebTrama(int fd){	
	//unsigned char auxLengthH, auxLengthL;
	char aux;
	int i;
	Trama tramaIn;
	
	tramaIn.type = '0';	
	i = 0;	
		//printf("no rebut res");
	while(i < 14){
		
		read(fd, &aux, sizeof(char));
		//printf("-%c\n", aux);
		tramaIn.origen[i] = aux;
		//printf("origen----%c\n", aux);
		i++;
	}
	//printf("type rebut");
	read(fd, &aux, sizeof(char));
	//printf("-%c\n", aux);
	tramaIn.type = aux;
	
	i = 0;
	//printf("dades rebut");
	//int maxH = 20;	
	
	while(i < 100){
		
		read(fd, &aux, sizeof(char));
		//printf("%d-%c\n", i, aux);
		tramaIn.data[i] = aux;
		
		i++;
		//printf("xxxxxxxxxxx\n");
	}
	//printf("fiii rebut\n");
	
	return tramaIn;	
}

DadesMet * EscriuADadesMet(Trama tra, char nome[31]){

	int i = 0, j = 0;
	DadesMet dades;
	DadesMet * dadesRet = NULL;

	char stringAux[7];
	//dades.nomEst = NULL;
	
	//dades.nomEst = malloc(sizeof(char)*strlen(nome));
	//strcpy(dades.nomEst, nome);
	for (int i = 0; i<= 31; i++){
		dades.nomEst[i] = nome[i];
		
	}
	//printf("NOOOOOOOOOM: %s \n", dades.nomEst);
	//strcpy(dades.nomEst, nome);
	/*int x = 0;
	while (nome[x] != '\0'){
		dades.nomEst[x] = nome[x];
		x++;
	}*/
	
		
		
		
	
	j = 0;
	i = 0;
	while(tra.data[i] != '#'){
		
		//printf("i: %d, value: %s \n", i, &tra.data[i]);
		i++;
		//j++;
	}
	//printf("PAS 0");
	i++;
	while(tra.data[i] != '#'){
		
		//printf("i: %d, value: %s		\n", i, &tra.data[i]);
		i++;
		//j++;
	}

		//printf("PAS 1");
	
	i++;
	j = 0;

	//
	
	//Llegim temperatura
	
	while(tra.data[i] != '#'){
		//printf("i: %d, value: %s		\n", i, &tra.data[i]);
		stringAux[j] = tra.data[i];
		i++;
		j++;
	}
	dades.temp = atof(stringAux);
	bzero( stringAux, 7 );
	//printf("temperatura %f\n", dades.temp);
	
	i++;
	j = 0;
	//Llegim humitat
	while(tra.data[i] != '#'){
		//printf("i: %d, value: %s\n", i, &tra.data[i]);
		stringAux[j] = tra.data[i];
		i++;
		j++;
	}
	dades.humitat = atoi(stringAux);
	bzero( stringAux, 7 );
	//printf("humitat %d\n", dades.humitat);

	i++;
	j = 0;
	//Llegim pressio
	while(tra.data[i] != '#'){
		//printf("i: %d, value: %s\n", i, &tra.data[i]);
		stringAux[j] = tra.data[i];
		i++;
		j++;
	}
	dades.pressio = atof(stringAux);
	bzero( stringAux, 7 );
	//printf("pressio %f\n", dades.pressio);	
	i++;
	j = 0;
	//Llegim pressipitacio
	
	while(tra.data[i] != '>'){
		//printf("i: %d, value: %s\n", i, &tra.data[i]);
		stringAux[j] = tra.data[i];
		i++;
		j++;
	}
	dades.precip = atof(stringAux);
	bzero( stringAux, 7 );
	//printf("precip %f\n", dades.precip);
	dadesRet =  &dades;
	
	return dadesRet;	
}


int EnviarTrama(int fd, Trama tramaEnviar){
	int j;
	
	
	/*printf("Trama == %c\n", tramaEnviar.type);
	printf("Origen == %s\n", tramaEnviar.origen);
	printf("Data == %s\n", tramaEnviar.data);*/
	
	switch ( tramaEnviar.type ){
		
		case 'O':

			for (j = 0; j < 14; j++){
				write(fd, &tramaEnviar.origen[j], sizeof(char));				
			}
			
			write(fd, &tramaEnviar.type, sizeof(char));
			
			for (j = 0; j < 100; j++){
				write(fd, &tramaEnviar.data[j], sizeof(char));				
			}
			
			break;		
	}
		 
	return 1;
}

Trama creaTramaInicial(Trama tramaIn){
	Trama tr;
	switch ( tramaIn.type ){
		case 'C':
		//printf("\n\n ES DAAAANYYY \n\n");
			if (esDanny(tramaIn)) {
				
				strcpy(tr.origen, "JACK");
				tr.type = 'O';
				strcpy(tr.data, "CONNEXIO OK");
			}else{
				
				strcpy(tr.origen, "JACK");
				tr.type = 'E';
				strcpy(tr.data, "ERROR");
				
			}
		break;
	}
	return tr;
}


Trama prepararTrama(char type, char *dades){
	//Trama trama;
	int i = 0;
	for(i = 0; i < 14; i++){
		trama.origen[i] = '\0';
	}
	for(i = 0; i < 100; i++){
		trama.data[i] = '\0';
	}
	switch( type ){
		
			case 'C':
		
				strcpy(trama.origen, "JACK");
				trama.type = 'C';							
				strcpy(trama.data, dades);
				break;
				
			case 'D':
		
				strcpy(trama.origen, "JACK");
				trama.type = 'D';							
				strcpy(trama.data, dades);
				break;
				
				
			case 'E':
				strcpy(trama.origen, "JACK");
				trama.type = 'E';							
				strcpy(trama.data, "ERROR");
				break;
				
			case 'Q':
				strcpy(trama.origen, "JACK");
				trama.type = 'Q';							
				strcpy(trama.data, dades);
				break;
				
				
		
	}
	return trama;
}

int esDanny(Trama tramaIn){
	int i, sonIguals;
	char nomDany[] = {'D','a','n','n','y','\0'}; 
	
	sonIguals = 1;
	for(i = 0; i < 6; i++){
		if (tramaIn.origen[i] != nomDany[i]) {
			sonIguals = 0;
		}
	}
	return sonIguals;
}

