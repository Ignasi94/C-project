#include "lloyd.h"
#include "trama.h"
/*
Trama tramaOut;
char type;
int Tenviat = 0;
*/

DadesMet * dadesMeteo;

unsigned int numDadesTotals = 0;


DadesMet * afegeixDadesMeteo(DadesMet dm, int * length){
	numDadesTotals++;
	int index;
	//printf("pas 1\n");
	if (numDadesTotals == 1){//Si es primer cop fem malloc
		dadesMeteo = (DadesMet *) malloc(sizeof(DadesMet));
		dadesMeteo[0] = dm;
		dadesMeteo[0].counter = 0;
		(*length)++;
		
	}else{//Si no és el primer cop, fem realloc si encara no existeix
		index = -1;
		//printf("pas 1\n");
		for(int i = 0; i <= (*length); i++){
			//printf("dm. nom est: \n dades[i]nomeest %s", dadesMeteo[i].nomEst);
			//printf("int : %d\n", i);
				int equals = 1;
			//if (dm.pid_tr == dadesMeteo[i].pid_tr){
				for(int j = 0; dm.nomEst[j] != '\0' ; j++){
					if (dm.nomEst[j] != dadesMeteo[j].nomEst[i]){
						equals = 0;
						printf("difeeerents\n");
					}
				}
			if(equals){
				index = i;
				printf("vreak\n");
				//printf("dm.pid= %ld, dadesmeteo[i].pid_tr = %ld\n", dm.pid_tr, dadesMeteo[i].pid_tr);
				//printf("indeeex %d: \n",index);
				//break;
				//return  dadesMeteo;
				break;
			}

		}
		printf("HOOLLAAA\n");
		//Mirem si ja existeix
		if (index < 0){//Cas que no existeixi
			(*length)++;
			//Ampliem una posició de memoria
			dadesMeteo = realloc(dadesMeteo, ((*length)+1)*sizeof(DadesMet));
			dadesMeteo[(*length)] = dm;
			dadesMeteo[(*length)].counter = 0;
			//printf("pas 1\n");
			
		}else{//Cas que ja existeixi
		//printf("pas 2\n");
			
			dadesMeteo[index].counter += 1;
			
			//Calcular la mitja
			//printf("Counter a l'hora de calcular mitja: %d\n", dadesMeteo[index].counter);
			float auxfactor1 = (float)(((float)(dadesMeteo[index].counter)) / (((float)(dadesMeteo[index].counter))+1));
			float auxfactor2 = (float)(((float)(1)) / (((float)(dadesMeteo[index].counter))+1));
			//printf("Factor 1 del valor anterior: %f", auxfactor1);
			//printf("Factor 2 del valor anterior: %f", auxfactor2);
			
			dadesMeteo[index].temp = (dadesMeteo[index].temp * auxfactor1  + dm.temp * auxfactor2) ;
			dadesMeteo[index].humitat = dadesMeteo[index].humitat *  auxfactor1 + dm.humitat * auxfactor2;
			dadesMeteo[index].pressio = dadesMeteo[index].pressio * auxfactor1 + dm.pressio * auxfactor2;
			dadesMeteo[index].precip = dadesMeteo[index].precip * auxfactor1    + dm.precip  * auxfactor2;
		}
		
	}
	//printf("pas 1\n");
	
	//printf("dades del array:\n");
	
	/*for(int j = 0; j <= ((*length)); j++){
		printf("index num: %d\n", j);
		printf("index nom: %s\n", dadesMeteo[j].nomEst);
		printf("Counter: %d\n", dadesMeteo[j].counter);
		printf("temp mitja: %f\n", dadesMeteo[j].temp);
		printf("humitat mitja: %f\n", dadesMeteo[j].humitat);
		printf("pressio mitja: %f\n", dadesMeteo[j].pressio);
		printf("precip mitja: %f\n\n\n\n", dadesMeteo[j].precip);		
		
		
	}*/
	
	//printf("Dades");
	
	return dadesMeteo;
	
}