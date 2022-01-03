#include "connexio.h"
#include "fitxerWendy.h"
#include "trama.h"

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
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

typedef struct {
    char type;
    char data[10];
} Frame;

int fd = -1, okAlarm = 0, server_socket, fd_client = 1, enviat;
int new_conn;
int *clients;
pthread_t *threads_id;
int count = 0;
char auxString[150];

//the thread function
void *connection_handler(void *);
Trama tramaIn, tramaOut;

int main (int argc, char *argv[]){
	
	DadesWendy dades;
	char nomF[20];
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
	//printf("%s\n", dades.ip);
	
	/*printf("PID DEL PROCES main ES id: %d\n",getpid());
	printf("ip: %s.\n",dades.ip);
	printf("port: %d.\n",dades.port);*/

	if (launch_server(dades, &server_socket)) {
		struct sockaddr_in c_addr;	
		socklen_t c_len = sizeof (c_addr);
		write(1, MeSG_SERVER_INIT, sizeof(MeSG_SERVER_INIT));
		//Declarem variable per crear threads
		pthread_t thread_id;
		int ret_pthread = 0;
		/* Initial memory allocation */
		//Iniciem array dinamic sockets
		clients = (int *) malloc(sizeof(int));
		//Iniciem array dinamic threads
		threads_id = (pthread_t *) malloc(sizeof(pthread_t));

		while (fd_client) {

			write(1, MeSG_WAIT_CONN, sizeof(MeSG_WAIT_CONN));
			//Si hi ha connexió de socket nova la acceptem
			fd_client = accept(server_socket, (void *) &c_addr, &c_len);
			
			//Guradem nova connexio socket al array dinamic
			clients[count] = fd_client;
			clients = realloc(clients, (count+1)*sizeof(int));
			
				
			//write(1, MSG_NEW_CONN, sizeof(MSG_NEW_CONN));				
			//printf("sha creat nou socket amb client amb id:%d", fd_client);
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
					sprintf(auxString, "ERROR: Could not create thread\n");
					write(1, auxString, strlen(auxString));
					//tancar_prog();
					//exit (EXIT_FAILURE);
				}else{
					//En el cas que s'hagi creat correctament, guardem el id del nou thread al array dinamic de threads_id
					threads_id[count] = thread_id;
					threads_id = realloc(threads_id, (count+1)*sizeof(pthread_t));					
				}
			}
			count++;
			
			//printf ("Connection accepted, whith thread id: %d\n", ret_pthread);
			//printf ("Nova connexi de %s:%hu\n",inet_ntoa (c_addr.sin_addr), ntohs (c_addr.sin_port));		 		
		}
		
		free(clients);
		clients = NULL;
		
		free(threads_id);
		threads_id = NULL;
		
		clients[count] = 0;
		wait(NULL);		
		
	}
	//reb la trama
	//free(dades.ip);

	return 0;
}

void *connection_handler(void *fd_cli){
	//printf("PID DEL THREAD ES id: %d\n",getpid());	
	signal(SIGINT, tancar_prog);
    //Get the socket descriptor
    int sock = *(int*)fd_cli;
	char *nomWendy;
	nomWendy = NULL;
	
	tramaIn = rebTrama(sock);
	

	if (tramaIn.type != 'C'){
		/*printf("Hem rebut nova trama  amb origen %s, type %c, i data %s\n", tramaIn.origen, tramaIn.type, tramaIn.data);
		close(server_socket);
		printf("HOLA, no hem rebut C, sino una altra merda\n");
		pthread_exit(NULL);*/
		
		if (sock > 0){
			sprintf(auxString, "Closing socket %d...\n", sock);
			write(1, auxString, strlen(auxString));
			close(sock);			
		}
		pthread_exit(NULL);
		//tancar_prog();
	}
	//printf("Hem rebut nova trama  amb origen %s, type %c, i data %s\n", tramaIn.origen, tramaIn.type, tramaIn.data);
	nomWendy = malloc(sizeof(char)*100);
	strcpy(nomWendy, tramaIn.data);
	
	sprintf(auxString, "New Connection: %s\n\n", nomWendy);
	write(1, auxString, strlen(auxString));
	

	tramaOut = creaTramaInicial(tramaIn);

	enviat = EnviarTrama(sock, tramaOut);

	//pthread_t pid_thread = pthread_self();
	DadesImatge dadesIm;
	
	while(1){
		
		
		tramaIn = rebTrama(sock);
		if (tramaIn.type != 'T'){
			sprintf(auxString, "\n\n\nProcess Wendy:\n");
			write(1, auxString, strlen(auxString));
		}
		//printf("Hem rebut nova trama amb origen %s, type %c, i data %s", tramaIn.origen, tramaIn.type, tramaIn.data);
		switch (tramaIn.type){
			
			case 'Q':
				//Un Danni es vol desconnectar		
				if (sock > 0){
					int closedSock = close(sock);
					sprintf(auxString, "Closing socket: %d, with closed state: %d\n", sock, closedSock);
					write(1, auxString, strlen(auxString));
				}
				pthread_exit(NULL);
				break;
				
			/*case 'D':
				//Han arribat dades atmosfèriques
				break;*/
				
			case 'I':
				//printf("Ens està arribant una imatge! ueeee\n");
				sprintf(auxString, "Reciving data from %s\n", nomWendy);
				write(1, auxString, strlen(auxString));
				dadesIm = rebTramaInicialImatge(tramaIn);
				if (rebImatge(dadesIm, sock)>= 0){
					//printf("Rebut correctament\n");
					//dadIm.nomIm
					//sprintf(auxString, "%s\n", dadesIm.nomIm);
					//write(1, auxString, strlen(auxString));
				}else{
					//printf("Error recepcio\n");
					sprintf(auxString, "Error; Reciving image\n");
					write(1, auxString, strlen(auxString));
				}
		
				//if rebIm < 0 llavors respondre amb error imatge
				break;
				
			case 'T':
				//Do nothing, es un test de connexio per part de danny
				/*sprintf(auxString, "Test rebut\n");
				write(1, auxString, strlen(auxString));*/
				break;
				
			default:

				sprintf(auxString, "Error; message not identified\n");
				write(1, auxString, strlen(auxString));
				if (sock > 0){
					int closedSock = close(sock);
					sprintf(auxString, "Closing socket %d, result: %d\n", sock, closedSock);
					write(1, auxString, strlen(auxString));
				}
			

				pthread_exit(NULL);
				break;
        }
	} 
	free(nomWendy);
	nomWendy = NULL;
    return 0;
} 




void tancar_prog(){
	
  if (server_socket != -1) close(server_socket);
  if (fd_client > 0) close(fd_client);
	
  char enter = '\n';
  //close(socket_fd); 
  for (int j = 0; j < count; j++){
	  //tanquem sockets
	  int closed;
	  if (clients[j] != -1){
		  closed = close(clients[j]);
	  }
	  //tanquem threads
	  pthread_exit(&threads_id[j]);
	  
	  printf("Close sock : %d wit value return %d\n", clients[j], closed);
  } 
  write(fd, &enter, 1);
  if (fd_client > 0) close(fd_client);
  write(1, SORTIR_, strlen(SORTIR_));
  raise(SIGKILL);

}