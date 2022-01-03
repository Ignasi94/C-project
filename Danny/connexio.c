#include "connexio.h"
int client_socket;

int CSocketJack(DadesEstacio dades){
	struct sockaddr_in server_address;
	char aux[50];
    
    int conn_status;
    client_socket = socket(AF_INET,SOCK_STREAM, 0);

    //strcpy(nomF, argv[1]);
	
    if(client_socket < 0){
        sprintf(aux, "Error creation socket with Jack\n");
		write(1, aux, strlen(aux));
		exit(-1);
    }

    //bzero(&server_address, sizeof (server_address));
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(dades.portJack);
    server_address.sin_addr.s_addr = inet_addr(dades.ipJack);
	sprintf(aux, "Connecting to Jack...\n");
	write(1, aux, strlen(aux));
    conn_status = connect(client_socket, (void*)&server_address, sizeof(server_address));
    if (conn_status == -1){

		  sprintf(aux, "Error connection socket with Jack\n");
		  write(1, aux, strlen(aux));
		  close(client_socket);
		  
		  
		  
          client_socket = -1;
    }else{
		sprintf(aux, "Connection with Jack ready.\n");
		write(1, aux, strlen(aux));
		//client_socket = 1;
	}
	 //char msg[] = "Hola!";
	// cridem sizeof i no strlen perqu msg s un array
	// cridar strlen tamb seria correcte
	//write (client_socket, msg, sizeof (msg));
    return client_socket;
}

int CSocketWendy(DadesEstacio dades){
	struct sockaddr_in server_address;
	char aux[50];
    
    int conn_status;
    client_socket = socket(AF_INET,SOCK_STREAM, 0);

    //strcpy(nomF, argv[1]);
	
    if(client_socket < 0){
        sprintf(aux, "Error creation socket with Wendy\n");
		    write(1, aux, strlen(aux));
		    exit(-1);
    }

    //bzero(&server_address, sizeof (server_address));
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(dades.portWendy);
    server_address.sin_addr.s_addr = inet_addr(dades.ipWendy);
	sprintf(aux, "Connecting to Wendy...\n");
	write(1, aux, strlen(aux));
    conn_status = connect(client_socket, (void*)&server_address, sizeof(server_address));
    if (conn_status == -1){

		  sprintf(aux, "Error connection socket with Wendy\n");
		  write(1, aux, strlen(aux));
		  close(client_socket);
		  
		  
		  
          client_socket = -1;
    }else{
		sprintf(aux, "Connection with Wendy ready.\n");
		write(1, aux, strlen(aux));
		//client_socket = 1;
	}
	 //char msg[] = "Hola!";
	// cridem sizeof i no strlen perqu msg s un array
	// cridar strlen tamb seria correcte
	//write (client_socket, msg, sizeof (msg));
    return client_socket;
}




