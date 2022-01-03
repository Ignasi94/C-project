#include "hallorann.h"
#include "trama.h"


int escriuDadesTxt(DadesMet * dadesMeteoA, int * length){
	//long res = -1;
	char aux_char[100];
	memset( aux_char, ' ', sizeof(char)*100 );
	int fd = open("hallorann.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);	
	if (fd <= 0) return 0;
	
	sprintf(aux_char, "error creacio del socket\n");
	
	//printf("sizeof de dade del tipus DadesMet : %f, and length %d==\n", (float) (sizeof(dadesMeteoA) / 8), *length);
	int i = 0;	
	
	if (*length >= 0 ){
		
		for(i = 0; i <= (*length); i++){
			sprintf(aux_char, "\ntemp: %.2f\nhumitat: %.2f\nPresio: %.2f\nPrecipitacio: %.2f\n\n", dadesMeteoA[i].temp, dadesMeteoA[i].humitat, dadesMeteoA[i].pressio, dadesMeteoA[i].precip);
			//write(1, auxString, strlen(auxString));
			write(fd, aux_char, (sizeof(aux_char)-1)); 	
		}
		
		
	}
	
	close (fd);

	return 0;
	
}