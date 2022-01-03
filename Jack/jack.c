#include "connexio.h"
#include "fitxerJack.h"

#include "trama.h"
#include "lloyd.h"
#include "hallorann.h"
#include "sem.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <netdb.h>
#include <strings.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>



DadesMet *dadesMeteo = NULL;	

typedef struct {

    char type;
    char data[10];

} Frame;

//DadesMet dadesMeteo;

//Declarem mutex
pthread_mutex_t sum_mutex;

char auxString[300];

semaphore *sem;

char *nomEstacio;
int fd = -1, okAlarm = 0, server_socket, fd_client = 1, pid_fork, enviat, aDades = 0;
int new_conn;
int *clients;
DadesJack dades;

pthread_t *threads_id;
int count = 0;


void handle_alarm_Hallorand(){

	//print();
	okAlarm = 1;
	aDades = 1;

}


//the thread function
void *connection_handler(void *);



int main (int argc, char *argv[]){
	
	DadesMet *dadesMeteo = NULL;	

	sem=malloc(sizeof(semaphore));
	SEM_constructor_with_name(&sem[0],ftok("jack.c",count));
	SEM_init(&sem[0],0);	
	
	//char auxString[20];
	char nomF[20];
	
	//pthread_t thread_socket;	
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
	
	//Iniciem Mutex
	pthread_mutex_init(&sum_mutex, NULL);

	
	//semaphore *sem;


	
	//Creamos el proceso hijo
    pid_fork = fork();	
	
	if (pid_fork < 0) {
        
		sprintf(auxString, "ERROR: creating fork \n");
		write(1, auxString, strlen(auxString));
		tancar_prog();
        exit(EXIT_FAILURE);
    } else if (pid_fork > 0){
		//Padre
		signal(SIGINT, tancar_prog);	
		
		if (launch_server(dades, &server_socket)) {
			
		
			///			
			struct sockaddr_in c_addr;	
			socklen_t c_len = sizeof (c_addr);
			
			write(1, MSG_SERVER_INIT, sizeof(MSG_SERVER_INIT));
			
			//Declarem variable per crear threads
			pthread_t thread_id;
			int ret_pthread = 0;
			
			/* Initial memory allocation */
			//Iniciem array dinamic sockets
			clients = (int *) malloc(sizeof(int));
			//Iniciem array dinamic threads
			threads_id = (pthread_t *) malloc(sizeof(pthread_t));

			
			
			while (fd_client) {

				write(1, MSG_WAIT_CONN, sizeof(MSG_WAIT_CONN));
				//Si hi ha connexió de socket nova la acceptem
				fd_client = accept(server_socket, (void *) &c_addr, &c_len);
				
				//Guradem nova connexio socket al array dinamic
				clients[count] = fd_client;
				clients = realloc(clients, (count+1)*sizeof(int));
					
				//write(1, MSG_NEW_CONN, sizeof(MSG_NEW_CONN));				

				//Mirem si s'ha creat be el socket
				if (fd_client < 0){
					sprintf(auxString, "ERROR: Connection NOT accepted\n");
					write(1, auxString, strlen(auxString));
					//tancar_prog();
					//exit (EXIT_FAILURE);
				}else{				
					//Creem thread
					ret_pthread = pthread_create( &thread_id , NULL ,  connection_handler , (void*) &fd_client);
					if( ret_pthread < 0){
						sprintf(auxString, "ERROR: could not create thread\n");
						write(1, auxString, strlen(auxString));
						tancar_prog();
						exit (EXIT_FAILURE);
					}else{
						//En el cas que s'hagi creat correctament, guardem el id del nou thread al array dinamic de threads_id
						threads_id[count] = thread_id;
						threads_id = realloc(threads_id, (count+1)*sizeof(pthread_t));					
					}
				}				
				count++;
				
				/*printf ("Connection accepted, whith thread id: %d\n", ret_pthread);
				printf ("Nova connexi de %s:%hu\n",inet_ntoa (c_addr.sin_addr), ntohs (c_addr.sin_port));	*/	 		
			}
						
			clients[count] = 0;
			   
			free(clients);
			clients = NULL;
			
			free(threads_id);
			threads_id = NULL;
			
			//Esperem que tanqui el fill
			wait(NULL);		
			//
			
		}
	} else {
		//HIJO	
			//semaphore *sem;
			sem=malloc(sizeof(semaphore));
			SEM_constructor_with_name(&sem[0],ftok("jack.c",count));		
	//SEM_init(&sem[count],0);
		int id_Memoria;	
		//signal(SIGINT, tancar_prog);
		/*printf("PID DEL PROCES FILL ES id: %d\n",getpid());
		printf("PID DEL PROCES PARE DESDE EL FILL ES id: %d\n",getppid());*/
		
		
		
		//ftock crea la clau, que va a la primera variable		
		//Creem memoria amb la clau

		//Creamos memoria compartida
		key_t clave;
			
		//Creem clau
		clave = ftok ("./fitxerJack.c", 22);
		if (clave == -1){
			
			sprintf(auxString, "ERROR: creating key\n");
			write(1, auxString, strlen(auxString));
			exit(0);
		}
		
		//Creem memoria amb la clau
		id_Memoria = shmget (clave, sizeof(DadesMet), 0777 | IPC_CREAT);
		if (id_Memoria == -1)
		{
			
			sprintf(auxString, "ERROR: No consigo Id para memoria compartida\n");
			write(1, auxString, strlen(auxString));
			
			
			exit (0);
		}
		
		//Fem que la nostra variable punter *dadesMeteo apunti a la zona de memòria creada.
		dadesMeteo = (DadesMet *)shmat (id_Memoria, (char *)0, 0);
		if (dadesMeteo == NULL)
		{
			
			sprintf(auxString, "ERROR: No consigo  mem compartida\n");
			write(1, auxString, strlen(auxString));
			exit (0);
		}

				

		
		//Iniciem signal sigalarm de 2 minuts
		signal(SIGALRM, handle_alarm_Hallorand);
		alarm(120);


		//DadesMet * dade;
		DadesMet * dadesMeteoArray;
		int lengthA = -1;
		while (1){
	
			/*if(okAlarm == 1){
				
				okAlarm = 0;
				//Iniciem signal sigalarm de 2 minuts
				signal(SIGALRM, handle_alarm_Hallorand);
				alarm(17);

			}	*/	

			//Esperem signal
			SEM_wait(&sem[0]);	
			signal(SIGALRM, handle_alarm_Hallorand);
			alarm(120);
			//Actualitza dades:d
			if (!aDades) {
			
				//lock mutex
				
				//pthread_mutex_lock (&sum_mutex);
				//Copiem la variable compartida a una variable del procés actual -> dade
				printf("escriu\n");
				
				DadesMet * dade;
				//dade->nomEst = NULL;
				//dade->nomEst = malloc(sizeof(char)*31);
				//strcpy(dade->nomEst, dadesMeteo->nomEst);
				dade = (dadesMeteo);// = (*EscriuADadesMet(tramaIn, nomEstacio));
				//dade->nomEst = NULL;
				//dade->nomEst = malloc(sizeof(char)*strlen(dadesMeteo->nomEst));
				//strcpy(dade->nomEst, dadesMeteo->nomEst);

				//printf("nooomjeje: %s\n",dade->nomEst );
				//printf("NOOOMESTACIOO %s\n",dadenomEst);
				sprintf(auxString, "FILLL nom est: %s \nTemp %f\nHumitat %f\nPressio %f\nPrecipitacio %f\n",dade->nomEst,  dade->temp, dade->humitat, dade->pressio, dade->precip);
				write(1, auxString, strlen(auxString));
				
				//unlock mutex
				//pthread_mutex_unlock (&sum_mutex);			
			
				dadesMeteoArray = afegeixDadesMeteo(*dade, &lengthA);
				

				//printf("\n\nDades extretes de afegeix dades metro són:\n\n Pid: %ld,\n", dadesMeteoArray[0].pid_tr);
				//aDades = 1;
			}
			
			if(aDades){
				//aDades = 0;
				sprintf(auxString, "\nWriting data in hallorann.txt\n");
				write(1, auxString, strlen(auxString));
				escriuDadesTxt(dadesMeteoArray, &lengthA);
				aDades = 0;


			}
				
		}	
		sprintf(auxString, "Closing son\n");
		write(1, auxString, strlen(auxString));
	}
	pthread_mutex_destroy(&sum_mutex);	
	//reb la trama
	//free(dades.ip);
    //server_run(socket_fd);
	return 0;
}

void *connection_handler(void *fd_cli)
{
	Trama tramaIn, tramaOut;
	
	//printf("PID DEL PROCES THREAD ES id: %d\n",getpid());
	//Creamos memoria compartida
	key_t clave;
		
	int id_Memoria;
	
	
	//Creem clau
	clave = ftok ("./fitxerJack.c", 22);
	if (clave == -1){
		sprintf(auxString, "ERROR: Creating key\n");
		write(1, auxString, strlen(auxString));
		exit(0);
	}
	
	//Creem memoria amb la clau
	id_Memoria = shmget (clave, sizeof(DadesMet), 0777 | IPC_CREAT);
	if (id_Memoria == -1)
	{
		
		sprintf(auxString, "ERROR: No consigo Id para memoria compartida\n");
		write(1, auxString, strlen(auxString));
		exit (0);
	}
	
	//Fem que la nostra variable punter *dadesMeteo apunti a la zona de memòria creada.
	dadesMeteo = (DadesMet *)shmat (id_Memoria, (char *)0, 0);
	if (dadesMeteo == NULL)
	{
		sprintf(auxString, "ERROR: No consegueixo mem compartida\n");
		write(1, auxString, strlen(auxString));
		exit (0);
	}
	
	
		
		
    //Get the socket descriptor
    int sock = *(int*)fd_cli;
	
    //int read_size;
    //char *message;// , client_message[2000];

	nomEstacio = NULL;
	
	tramaIn = rebTrama(sock);
	if (tramaIn.type != 'C'){
		sprintf(auxString, "Closing socket %d...\n", server_socket);
		write(1, auxString, strlen(auxString));
		close(server_socket);
		tancar_prog();
	}
	//printf("Hem rebut nova trama amb origen %s, type %c, i data %s\n", tramaIn.origen, tramaIn.type, tramaIn.data);
	nomEstacio = malloc(sizeof(char)*100);
	strcpy(nomEstacio, tramaIn.data);
	
	sprintf(auxString, "New Connection: %s\n\n", nomEstacio);
	write(1, auxString, strlen(auxString));
	tramaOut = creaTramaInicial(tramaIn);
	enviat = EnviarTrama(sock, tramaOut);
	
	//pid_t pid_thread = getpid();
	//pthread_t pid_thread = pthread_self();
	//printf("El nou thread te un pid de:  %ld\n", pid_thread);

			
		
	//SEM_init(&sem[count],0);
	while(1){
		tramaIn = rebTrama(sock);
		if (tramaIn.type != 'T'){
			sprintf(auxString, "Process Jack:\n");
			write(1, auxString, strlen(auxString));
		}
		//printf("Hem rebut nova trama amb origen %s, type %c, i data %s", tramaIn.origen, tramaIn.type, tramaIn.data);
		
		switch (tramaIn.type){
			case 'Q':
				//Un Danni es vol desconnectar		
				if (sock > 0){
					int closedSock = close(sock);
					//printf("holaaaaa, sha tancat un Danny amb socket sock: %d, amb resultat%d\n", sock, closedSock);
					sprintf(auxString, "Closing socket: %d, with closed state: %d\n", sock, closedSock);
					write(1, auxString, strlen(auxString));
				}

				pthread_exit(NULL);

				break;
		
				
			case 'D':
				//Han arribat dades atmosfèriques
				//printf("apunt de strcpy");
				//pthread_mutex_lock (&sum_mutex);
				//printf("apunt de strcpy");
				
				(*dadesMeteo) = (*EscriuADadesMet(tramaIn, nomEstacio));
				sprintf(auxString, "\nTemp %f\nHumitat %f\nPressio %f\nPrecipitacio %f\n", dadesMeteo->temp, dadesMeteo->humitat, dadesMeteo->pressio, dadesMeteo->precip);
				
				write(1, auxString, strlen(auxString));
					/*for (int i = 0; i<= 31; i++){
						
						printf("NOOOOOOOOOM: %c \n", dadesMeteo->nomEst[i]);
					}*/
					
				
				//pthread_mutex_unlock (&sum_mutex);
				
				//Enviem un signal (semàfors per sincronització) per avisar al fork fill Lloyd de que hi ha noves dades
				SEM_signal(&sem[0]);
				
				

				break;
				
			case 'T':
				//Do nothing, es un test de connexio per part de danny
				/*sprintf(auxString, "Test rebut\n");
				write(1, auxString, strlen(auxString));*/
				break;


			default:
				
				
				sprintf(auxString, "Message not identified\n");
				write(1, auxString, strlen(auxString));
				sprintf(auxString, "Closing socket %d...\n", sock);
				write(1, auxString, strlen(auxString));
				//tancar_prog();
				if (sock > 0){
					int closedSock = close(sock);
					
					sprintf(auxString, "Closed socket: %d, with state: %d\n", sock, closedSock);
					write(1, auxString, strlen(auxString));
				}
				

				pthread_exit(NULL);
				break;
        }

	}
	free(nomEstacio);
	nomEstacio = NULL;

         
    return 0;
} 




void tancar_prog(){
  Trama tramaOut;

  char type;
  if (server_socket != -1) close(server_socket);
  kill(pid_fork, SIGKILL);
  kill((int) (pid_fork+1), SIGKILL);
  if (fd_client > 0) close(fd_client);
  char enter = '\n';
  //close(socket_fd);
  for (int j = 0; j < count; j++){
	  //tanquem sockets
	  	type = 'Q';
		tramaOut = prepararTrama(type, "Desconnecta");
		EnviarTrama(clients[j], tramaOut);
	  int closed;
	  if (clients[j] != -1){
		  closed = close(clients[j]);
	  }
	  //tanquem threads
	  pthread_exit(&threads_id[j]);
	  
	  sprintf(auxString, "Close sock : %d wit value return %d\n", clients[j], closed);
	  write(1, auxString, strlen(auxString));
	  
  }
  
  free(dadesMeteo);
  dadesMeteo = NULL;

  free(nomEstacio);
  nomEstacio = NULL;
  free(clients);
  clients = NULL;
  free(threads_id);
  threads_id = NULL;
  free(&sem[0]);
  //connection_handler = NULL;
  free(dadesMeteo);
  dadesMeteo = NULL;  
  write(fd, &enter, 1); 
  write(1, SORTIR_, strlen(SORTIR_)); 
  kill(pid_fork, SIGKILL);
  kill((int) (pid_fork+1), SIGKILL);
  int wstatus;
  //printf("waiting killing process");
  sprintf(auxString, "aiting killing process\n");
  write(1, auxString, strlen(auxString));
  if (waitpid(pid_fork, &wstatus, 0) == -1) {
	perror("waitpid");
	exit(EXIT_FAILURE);
  }
  raise(SIGKILL);
  exit(0);
}