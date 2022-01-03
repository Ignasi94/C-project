#include "trama.h"
#include<sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

Trama trama;

int fichero;
int maxH = 15;

#define STDIN 0
#define STDOUT 1

char nom_imatge[31];
char mida_imatge[33];
char md5sum_imatge[33], auxString[50];

int compareArrays(char * a, char * b);

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
		tramaIn.data[i] = aux;	
		//printf("-%c\n", aux);		
		i++;
	}
	//printf("fiii rebut\n");
	
	return tramaIn;	
}




int rebImatge(DadesImatge dadIm, int fd){
	long long numTrames = dadIm.midaIm / 100;
	long long resid = dadIm.midaIm % 100;
	//printf("num trames: %lli \n", numTrames);
	//printf("residu: %lli\n", resid);

    /*char * dadesImString;
	dadesImString = NULL;
	dadesImString = (char *)malloc(sizeof(char));*/

	Trama tramaIn;
	
	long long i = 0;
	long long j = 0;
	
	
	//Creem fitxer Imatge
	int fd_im = open(dadIm.nomIm, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);	
	if (fd_im <= 0){

		sprintf(auxString, "ERROR: Error opening image file\n");
		write(1, auxString, strlen(auxString));
	}
	
	sprintf(auxString, "\nName file image: %s\n", dadIm.nomIm);
	write(1, auxString, strlen(auxString));
	
	while (j < (numTrames + 1)) {
		tramaIn = rebTrama(fd);
		//printf("Origen: %s\nTyper: %c\nData: %s\n", tramaIn.origen, tramaIn.type, tramaIn.data);
		if (tramaIn.type != 'F'){
			return -1;
		}
		
		int k = 0;
		
		if (j < numTrames){
			while (k < 100 ){
				//printf("%c", tramaIn.data[k]);
				write(fd_im, &tramaIn.data[k], (sizeof(char))); 	
				k++;
				i++;
			}
		}else{
			while (k < resid ){				
				//printf("%c", tramaIn.data[k]);
				write(fd_im, &tramaIn.data[k], (sizeof(char))); 
				k++;
				i++;
			}
		}
		j++;
	}
	//Tanquem fitxer.
	close (fd_im);
	
	/*fd_im = open(dadIm.nomIm, O_RDONLY);
	int ret;
	char caracter;
	while ((ret = read(fd_im, &caracter, 1)) > 0){
		//read(fd, &caracter, 1);
		//strDadesImUnaTrama[iImatgeTram] = caracter;//dadesImatge[iImatge];
		printf("%c", caracter);
		//iImatge++;
		//iImatgeTram++;
	}
	close (fd_im);*/
	//printf("\n Fi reb trama: Trama:\n");
	sprintf(auxString, "md5sumIm rebut: \n%s\n", dadIm.md5sumIm);
	write(1, auxString, strlen(auxString));
	
	
	//Calculem md5sum:
	int fd_p[2];
	char *args[] = { "md5sum", dadIm.nomIm, NULL};
	//int fd=open("test",O_CREAT|O_WRONLY,S_IRWXU);
	pipe(fd_p);
	pid_t pid=fork();

	if(!pid){	
		dup2(fd_p[1], STDOUT);
		close(fd_p[0]);
		close (fd_p[1]);
		execvp(args[0], args);
	}
	dup2(fd_p[0], STDIN);
	//printf("%s",&fd_p[0]);
	close(fd_p[0]);
	close(fd_p[1]);
	
	//char buff[1000]={0};
	char * stringmd5sum;
	stringmd5sum = malloc(sizeof(char)*100);
	read(STDIN_FILENO,stringmd5sum,250);
	stringmd5sum[32] = '\0';
	
	sprintf(auxString, "md5sum calculat:\n%s\n",stringmd5sum);	
	write(1, auxString, strlen(auxString));	
	wait(NULL);
	waitpid(pid, NULL, 0);
	
	if (compareArrays(stringmd5sum, dadIm.md5sumIm)){
		//free(stringmd5sum);
		//stringmd5sum = NULL;
		sprintf(auxString, "MD5SUM CORRECTE\n");	
		write(1, auxString, strlen(auxString));	
		
		return 1;
		
	}else{
		//free(stringmd5sum);
		//stringmd5sum = NULL;
		sprintf(auxString, "MD5SUM INCORRECTE\n");	
		write(1, auxString, strlen(auxString));	

		return 0;
		
	}	
}


int compareArrays(char * a, char * b) {
  int ii;
  for(ii = 0; ii < 32; ii++) {
	//printf("a: = %c, b: = %c\n", a[ii] , b[ii]);
    if (a[ii] != b[ii]) return 0;
  }
  return 1;
}



DadesImatge rebTramaInicialImatge(Trama tra){

	int i = 0, j = 0;
	DadesImatge di;

	/*char * nom_imatge[31];
	char * mida_imatge[33];
	char * md5sum_imatge[33];*/
	
	/*char * nom_imatge;
	char * mida_imatge;
	char * md5sum_imatge;
	
	nom_imatge = malloc(sizeof(nom_imatge)*31);
	mida_imatge = malloc(sizeof(mida_imatge)*33);
	md5sum_imatge = malloc(sizeof(md5sum_imatge)*33);*/
	

	memset(nom_imatge, '\0', sizeof(char)*31);
	memset(mida_imatge, '\0', sizeof(char)*33);
	memset(md5sum_imatge, '\0', sizeof(char)*33);
	
	j = 0;
	i = 1;	
	//Llegim nom
	
	while(tra.data[i] != '#'){
		nom_imatge[j] = tra.data[i];
		i++;
		j++;
	}
	di.nomIm = malloc(sizeof(nom_imatge));
	strcpy(di.nomIm, nom_imatge);
	
	//printf("nom imatge %s\n", di.nomIm);	
	
	i++;
	j = 0;
	//Llegim humitat
	while(tra.data[i] != '#'){
		//printf("i: %d, value: %s\n", i, &tra.data[i]);
		mida_imatge[j] = tra.data[i];
		i++;
		j++;
	}
	long long mida = atoll(mida_imatge);
	di.midaIm = mida;
	//bzero( stringAux, 7 );
	//printf("mida %lld\n", di.midaIm);
	
	//printf("PAS 3");
	i++;
	j = 0;
	//Llegim pressio
	while(tra.data[i] != '>'){
		//printf("i: %d, value: %s\n", i, &tra.data[i]);
		md5sum_imatge[j] = tra.data[i];
		i++;
		j++;
	}
	di.md5sumIm = malloc(sizeof(md5sum_imatge));
	strcpy(di.md5sumIm, md5sum_imatge);
	//printf("md5sum_imatge %s\n", di.md5sumIm);

	return di;
}


int EnviarTrama(int fd, Trama tramaEnviar){
	int j;
	
	
	/*printf("Trama == %c\n", tramaEnviar.type);
	printf("Origen == %s\n", tramaEnviar.origen);
	printf("Data == %s\n", tramaEnviar.data);*/
	
	switch ( tramaEnviar.type ){
		
		case 'O':

			for (j = 0; j < 14; j++){
				//printf("lletra: %c", tramaEnviar.origen[j]);
				write(fd, &tramaEnviar.origen[j], sizeof(char));
			}
			//printf("type: %c", tramaEnviar.type);
			write(fd, &tramaEnviar.type, sizeof(char));
			
			for (j = 0; j < 100; j++){
				//printf("lletra: %c", tramaEnviar.data[j]);
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

			if (esDanny(tramaIn)) {
				
				strcpy(tr.origen, "WENDY");
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

