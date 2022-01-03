#include "connexio.h"
#include "fitxerWendy.h"
#include "trama.h"

char auxString[70];
void server_run(int *server_socket, int *fd_client) {
    struct sockaddr_in c_addr;
	int aux = 0;
    socklen_t c_len = sizeof (c_addr);
	
    //write(1, MeSG_SERVER_INIT, sizeof(MeSG_SERVER_INIT));

    while (!aux) {

        //write(1, MeSG_WAIT_CONN, sizeof(MeSG_WAIT_CONN));
        *fd_client = accept(*server_socket, (void *) &c_addr, &c_len);
        //write(1, MSG_NEW_CONN, sizeof(MSG_NEW_CONN));
		
		if (*fd_client < 0){

			sprintf(auxString, "ERROR: Connection to socket\n");
			write(1, auxString, strlen(auxString));
			
			exit (EXIT_FAILURE);
		}else{
			
			//break;
			aux = 1;
		}
		//printf ("Nova connexi de %s:%hu\n",inet_ntoa (c_addr.sin_addr), ntohs (c_addr.sin_port));		 		
	}
}





int launch_server(DadesWendy dades, int *socket_fd) {
    struct sockaddr_in s_addr;
		
    *socket_fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char * ip;
	ip = (char *)malloc(sizeof(char)*20);
	//strcpy(ip, dades.ip);
	for (int i = 0; i<17; i++){
		ip[i] = dades.ip[i];	
	}


    if (*socket_fd < 0){
		
        write(1, ERROR_CREAR_SOCKET_A, sizeof(ERROR_CREAR_SOCKET_A));
	}else {
		
		memset(&s_addr, 0, sizeof(s_addr));
        s_addr.sin_family = AF_INET;	


        s_addr.sin_addr.s_addr = inet_addr(ip);
		free(ip);
		ip = NULL;
		s_addr.sin_port = htons(dades.port);
        
        if (bind(*socket_fd, (void *)&s_addr, sizeof (s_addr)) < 0){//assignamos un puerto al socket
            write(1, ERROR_BIND, sizeof(ERROR_BIND));
        }else {		
         	listen(*socket_fd, LISTEN_BACKLOG);
            return 1;
        }
    }
    return 0;
}