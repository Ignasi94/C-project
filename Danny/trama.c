#include "trama.h"
#include "fitxerConfig.h"
#include "connexio.h"
Trama trama;
Trama tramaaux;
//DadesFitxer df;
int fichero;
unsigned int res = 0;
char *dadesF;

Trama rebTrama(int fd){	
	//unsigned char auxLengthH, auxLengthL;
	char aux;
	int i;
	Trama tramaIn;
	
	tramaIn.type = 'O';
	i = 0;
		//printf("rebraaaas?? \n");
	while(i < 113){
		
		read(fd, &aux, sizeof(char));
		//printf("-%c", aux);
		//casella on rebem el type
		if (i == 14){
			tramaIn.type = aux;
		}
		//printf("-%c\n", aux);
		
		//guardem Origen
		if (i < 14){
			tramaIn.origen[i] = aux;
		}
		
		//guardem Data
		if (i > 14){
			tramaIn.data[i - 15] = aux;
			
		}
		//tramaIn.origen[i] = aux;
		//printf("origen----%c\n", aux);
		i++;
	}

	return tramaIn;	
}

Trama prepararTramaEstacio(char type, DadesEstacio de){
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
		
				strcpy(trama.origen, "Danny");
				trama.type = 'C';							
				strcpy(trama.data, de.nomEst);
				break;
				
				
			case 'E':
				strcpy(trama.origen, "Danny");
				trama.type = 'E';							
				strcpy(trama.data, "ERROR");
				break;
				
			case 'Q':
				strcpy(trama.origen, "Danny");
				trama.type = 'Q';							
				strcpy(trama.data, de.nomEst);
				break;
					
	}
	return trama;
}

Trama prepararTramaFImatge(char type, char dades[100]){
	//Trama trama;
	int i = 0;
	for(i = 0; i < 14; i++){
		trama.origen[i] = '\0';
	}
	for(i = 0; i < 100; i++){
		trama.data[i] = '\0';
	}
	strcpy(trama.origen, "Danny");
	trama.type = type;							
	//strcpy(trama.data, dades);
	for(int j = 0; i < 100; i++){
		trama.data[j] = dades[j];
	}
	return trama;

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
		
				strcpy(trama.origen, "Danny");
				trama.type = 'C';							
				strcpy(trama.data, dades);
				break;
				
			case 'D':
		
				strcpy(trama.origen, "Danny");
				trama.type = 'D';							
				strcpy(trama.data, dades);
				break;
				
				
			case 'E':
				strcpy(trama.origen, "Danny");
				trama.type = 'E';							
				strcpy(trama.data, "ERROR");
				break;
				
				
			case 'Q':
				strcpy(trama.origen, "Danny");
				trama.type = 'Q';							
				strcpy(trama.data, dades);
				break;
				
				
			case 'I':
				strcpy(trama.origen, "Danny");
				trama.type = 'I';							
				strcpy(trama.data, dades);
				break;
				
			case 'T':
				strcpy(trama.origen, "Danny");
				trama.type = 'T';							
				strcpy(trama.data, dades);
				break;
				
				
			case 'F':
				strcpy(trama.origen, "Danny");
				trama.type = 'F';							
				//strcpy(trama.data, dades);
				for(int j = 0; j < 100; j++){
					trama.data[j] = dades[j];
					//printf("c-%c\n", trama.data[j]);
				}
				break;
		
	}
	/*printf("Tipus == %c\n", trama.type);
	printf("Origen == %s\n", trama.origen);
	printf("Data == %s\n", trama.data);*/
	return trama;
}

int EnviarTrama(int fd, Trama tramaEnviar){
	int j;
	int ret = 0;
	
	/*printf("Tipus == %c\n", tramaEnviar.type);
	printf("Origen == %s\n", tramaEnviar.origen);
	printf("Data == %s\n", tramaEnviar.data);*/
			
			ret = 1;
			//printf("apunt denviar");
			for (j = 0; j < 14; j++){
				
				int x = write(fd, &tramaEnviar.origen[j], sizeof(char));	
				if (x < 1) {
					ret = 0;
					break;
				}
				
			}
			//printf("apunt denviar type\n");
			write(fd, &tramaEnviar.type, sizeof(char));
			//printf("apunt denviar trama\n");
			j= 0;
			for (j = 0; j <100; j++){
				
				write(fd, &tramaEnviar.data[j], sizeof(char));
								
				
			}
			//printf("tot enviat\n");

			
	return ret;
}
/* 

int ompleTrama(int tipus, DadesEstacio dTel, int *tipusFitxer, int fd){
	
		return 1;
}




int prepararIEnviarTrama(int fd){
  
	return 1;
}



#include "connexioM.h"


int consultaDir(){
	
			return 0;
}

int guardaDataTxt(){
	

				return 0;
}




Trama rebTrama(int fd){	

	return 1;	
}*/

