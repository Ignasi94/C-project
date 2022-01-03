#include "fitxerConfig.h"
#include "direct.h"
#include "connexio.h"
#include "fitxerConfig.h"
#include "trama.h"

#include <pthread.h>

DadesFitxer df;
DadesEstacio dades;
Trama tramaOut, tramaIn;
int fd = -1, okAlarm_Jack = 0,okAlarm_Wendy = 0, id_socket_Jack, id_socket_Wendy, tipus = 0, enviat = 0, connectat_jack = 0, connectat_wendy = 0, flag_connection = 0, test_conn = 0;
char type;
char auxString[40];
int descon_jack = 0, descon_wendy = 1;
pthread_t *threads_id;

void handle_alarm_Fitxers(){
	okAlarm_Jack = 1;
	okAlarm_Wendy = 1;
}

void handle_alarm_Imatges(){
	okAlarm_Jack = 1;
	okAlarm_Wendy = 1;
	
}



void handle_alarm_check_connection(){
	flag_connection = 1;
}

void *connection_handler_jack();
void *connection_handler_wendy();


int main (int argc, char *argv[]){
	char nomF[20];
	//int error_socket = 0;

	//df.nomFitx = NULL;
	signal(SIGINT, tancar_prog);
	if(argc != 2){
		write(1, EFITX_, strlen(EFITX_));
		exit(EXIT_FAILURE);
	}
	strcpy(nomF, argv[1]);
	if(!obtDades(&dades, nomF, fd)){

		write(1, EFITX_, strlen(EFITX_));
		exit(EXIT_FAILURE);
	}
	
	sprintf(auxString, "Starting %s\n", dades.nomEst);
	write(1, auxString, strlen(auxString));

	//Declarem variable per crear threads
	pthread_t thread_id;
	int ret_pthread = 0;
	threads_id = (pthread_t *) malloc(sizeof(pthread_t)*2);
	

	//Creem thread Wendy
	ret_pthread = pthread_create( &thread_id , NULL ,  connection_handler_wendy, NULL);
	if( ret_pthread < 0){
		//pthread_create(&threads_id[0], NULL, Makis, &NumMakis);
		//printf ("could not create thread\n");
		sprintf(auxString, "Could not create thread wendy\n");
		write(1, auxString, strlen(auxString));
		tancar_prog();
		exit (EXIT_FAILURE);
	}else{
		//En el cas que s'hagi creat correctament, guardem el id del nou thread al array dinamic de threads_id
		threads_id[1] = thread_id;
		//sleep(1);
						
	}
	
	
	
	//Creem thread Jack
	ret_pthread = pthread_create( &thread_id , NULL ,  connection_handler_jack, NULL);
	if( ret_pthread < 0){
		//pthread_create(&threads_id[0], NULL, Makis, &NumMakis);
		sprintf(auxString, "Could not create thread Jack\n");
		write(1, auxString, strlen(auxString));
		tancar_prog();
		exit (EXIT_FAILURE);
	}else{
		//En el cas que s'hagi creat correctament, guardem el id del nou thread al array dinamic de threads_id
		threads_id[0] = thread_id;
							
	}
	
	
	//printf("\n");

	
	while(1){
		/*if (descon_jack && descon_wendy) {
			printf("descondectaaar!\n");
			tancar_prog();
		}*/
			
	}
	return 0;
}


void *connection_handler_jack(){
	
	signal(SIGINT, tancar_prog);
	id_socket_Jack = CSocketJack(dades);
	type = 'C';
	tramaOut = prepararTramaEstacio(type, dades);
	enviat = EnviarTrama(id_socket_Jack, tramaOut);
	//printf("tot enviat222\n");	
	tramaIn = rebTrama(id_socket_Jack);
	/*printf("Trama rebuda == \n");
	printf("Tipus == %c\n", tramaIn.type);
	printf("Origen == %s\n", tramaIn.origen);
	printf("Data == %s\n", tramaIn.data);*/
	//printf("return number %d\n", strcmp(tramaIn.data, "CONNEXIO OK"));
	if (tramaIn.type == 'O' && (strcmp(tramaIn.data, "CONNEXIO OK") == 0)){
		connectat_jack = 1;
	} else {
		descon_jack = 1;
		tancar_prog();
		//sprintf(auxString, "NO HEM TROBAT SERVIDOR JACK\n");
		//write(1, auxString, strlen(auxString));
		//return 0;
	}
	
	signal(SIGALRM, handle_alarm_Fitxers);
	//signal(SIGALRM, handle_alarm_Imatges);
	alarm(dades.temps);

	if(connectat_jack){
		while(1){	
			if(okAlarm_Jack == 1){
	
				sprintf(auxString, "Process Danny:\n");
				write(1, auxString, strlen(auxString));
					
				if (!consultaDir(&df, id_socket_Jack, dades, 't')){
					tancar_prog();	
				}
							
				signal(SIGALRM, handle_alarm_Fitxers);
				alarm(dades.temps);
				okAlarm_Jack=0;
				/*if (enviat == 1){				
					sprintf(auxString, "Enviat\n");
					write(1, auxString, strlen(auxString));
				}*/
			}
		}
	}
	return 0;
}

void *connection_handler_wendy(){
	
	signal(SIGINT, tancar_prog);
	id_socket_Wendy = CSocketWendy(dades);
	type = 'C';
	tramaOut = prepararTramaEstacio(type, dades);
	enviat = EnviarTrama(id_socket_Wendy, tramaOut);
	//printf("tot enviat222\n");	
	tramaIn = rebTrama(id_socket_Wendy);
	/*printf("Trama rebuda == \n");
	printf("Tipus == %c\n", tramaIn.type);
	printf("Origen == %s\n", tramaIn.origen);
	printf("Data == %s\n", tramaIn.data);*/
	//printf("return number %d\n", strcmp(tramaIn.data, "CONNEXIO OK"));
	if (tramaIn.type == 'O' && (strcmp(tramaIn.data, "CONNEXIO OK") == 0)){
		connectat_wendy = 1;
		//printf("HEM TROBAT SERVIDOR Wendy\n");
	} else {
		descon_wendy = 1;
		tancar_prog();
		//sprintf(auxString, "NO HEM TROBAT SERVIDOR Wendy\n");
		//write(1, auxString, strlen(auxString));
		//return 0;
	}
	

	//printf("\n");
	signal(SIGALRM, handle_alarm_Fitxers);
	alarm(dades.temps);

	if (connectat_wendy){
		//printf("connectat wendy\n");
		while(1){	
			
			
			/*if (flag_connection == 1){
				char x = 't';
				printf("test  Connection : %d\n", test_conn);
				test_conn = write(fd, &x, sizeof(char));
				printf("test  Connection : %d\n", test_conn);
			}*/
			
			if(okAlarm_Wendy == 1){
				//Enviem trama per comprobar si hi ha connexió				
				
				sprintf(auxString, "Process Wendy:\n");
				write(1, auxString, strlen(auxString));
					
				if (!consultaDir(&df, id_socket_Wendy, dades, 'i')){
					close(id_socket_Wendy);
					tancar_prog();	
				}

				signal(SIGALRM, handle_alarm_Fitxers);
				alarm(dades.temps);
				okAlarm_Wendy=0;
				
				
				//if (enviat == 1) printf("enviat");
			}
		}
	}
	return 0;
	
	
}



void tancar_prog(){
	
  int * ptr [2];

  char enter = '\n';
  
  if (fd > 0) close(fd);

  if (connectat_jack) {
		descon_wendy = 1;
	  	type = 'Q';
		tramaOut = prepararTramaEstacio(type, dades);
		enviat = EnviarTrama(id_socket_Jack, tramaOut);
		//close(id_socket_Jack);
		if (id_socket_Jack > 0) close(id_socket_Jack);
		
  }
  
  if (connectat_wendy) {
		descon_jack = 1;
	  	type = 'Q';
		tramaOut = prepararTramaEstacio(type, dades);
		enviat = EnviarTrama(id_socket_Wendy, tramaOut);
		if (id_socket_Wendy > 0) close(id_socket_Wendy);
		
  }
    //printf("enviat q a jack per tancart\n");
  //if (id_socket_Jack > 0) close(id_socket_Jack);
  raise(SIGKILL);
  //Tanquem thread jack
  pthread_exit(&threads_id[0]);
  //Tanquem thread wendy
  pthread_exit(&threads_id[1]);
  
  //Esperem a que es tanquin els dos processos 
  pthread_join (threads_id [0], (void **) & (ptr [0]));
  pthread_join (threads_id [1], (void **) & (ptr [1]));
  
  
  
  write(fd, &enter, 1);

  //df.nomFitx = NULL;
  dades.nomEst = NULL;
  write(1, SORTIR_, strlen(SORTIR_));
  raise(SIGKILL);
  

}