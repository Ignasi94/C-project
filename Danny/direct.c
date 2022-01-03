#include "direct.h"
#include "trama.h"
#include <stdlib.h>
#include <pthread.h>
#include<sys/wait.h>

#define STDIN 0
#define STDOUT 1
Trama tramaOut;
char type;
int Tenviat = 0;
char auxString[290];

char* itoa(int value, char* result, int base);

int consultaDir(DadesFitxer *df, int id_socket, DadesEstacio dades, char ty){
		  char aux[18], buff[200], *text, aux_char, *textImatge;
		  int numReal = 0, count = 0;
		  long res = -1;
		  DIR *dir;
		  //char hola[30] = "files/20170707-214516.dat\0";
		  char aux1[70];
		  int bytes, fd = -1;  
		  int llargadaNomFitxer, status;
		  int numf = 0;
		 
		  //en ent estarà la info del archiu actual
		  struct dirent *ent;
	
		  //Obrim directori actual
		  //printf("ara anem a obrir:%s.\n", dades.nomCarpeta); //dir = opendir (dades.nomCarpeta);)
		  //char *buffer ;//[100];
		  //buffer = NULL;
		 
		  dir = opendir (dades.nomCarpeta);

		  //mirem possibles errors d'opertura
		  if (dir == NULL) {
			  write(1, ERR_OP_DIR, strlen(ERR_OP_DIR));
			  return 0;
		  }
		  
		  numf = 0;
		  while ((ent = readdir (dir)) != NULL){
			   numf++;
			   numReal = numf - 2;				
			   
		  }
		  

		  sprintf(auxString, "%d Files found.\n", numReal);
		  write(1, auxString, strlen(auxString));
		  
		  
		  closedir (dir);
			
			
		  count = 0;
		  text = NULL;
		  textImatge = NULL;
		  //text = malloc(sizeof(char));
		  dir = opendir (dades.nomCarpeta);
		  numf = 0;
		   while ((ent = readdir (dir)) != NULL){
			   numf++;
			   //df->nomFitx = malloc(sizeof(char));
				if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0)  ){
						strcpy(aux, ent->d_name);
						llargadaNomFitxer = strlen(ent->d_name);
						//df->nomFitx = realloc(df->nomFitx, (llargadaNomFitxer+1)*sizeof(char));
						strcpy(df->nomFitx, ent->d_name);
						
						
						strcpy(aux1, dades.nomCarpeta);
						strcat(aux1, "/");
						strcat(aux1, df->nomFitx);
						//printf("LLARGAADA NOM FITXER%d, crido desde el tipus: %c", llargadaNomFitxer, ty);
						text = malloc(sizeof(char)*20);
						if ( ty == 't' &&df->nomFitx[llargadaNomFitxer-1] == 't' && df->nomFitx[llargadaNomFitxer-2] == 'x' && df->nomFitx[llargadaNomFitxer-3] == 't' && df->nomFitx[llargadaNomFitxer-4] == '.'){
																
							    sprintf(auxString, "File name: %s\n", df->nomFitx);
								write(1, auxString, strlen(auxString));
								
								df->tipus = 't';
								fd = open(aux1, O_RDONLY);
								if (fd <= 0) return 0;
								
								text[count] = '<';
		
								if(aux_char == 'x' && res == 23){
										
								}
								
								text = realloc(text, (count+1)*sizeof(char));
								count++;
								
								res = read(fd, &aux_char, 1);
								while (aux_char != '\n') {//while (res != 0 && aux_char != '\0') {
									
									text[count] = aux_char;
									text = realloc(text, (count+1)*sizeof(char));
									res = read(fd, &aux_char, 1);
									count++;
								}
								text[count-1] = '#';
								text = realloc(text, (count+1)*sizeof(char));
				
								text = realloc(text, (count+1)*sizeof(char));
								
								
																
								res = read(fd, &aux_char, 1);
								while (aux_char != '\n') {
									
									text[count] = aux_char;
									text = realloc(text, (count+1)*sizeof(char));
									res = read(fd, &aux_char, 1);
									count++;
								}
								
								text[count-1] = '#';
								text = realloc(text, (count+1)*sizeof(char));							
																
								res = read(fd, &aux_char, 1);
								while (aux_char != '\n') {
									
									text[count] = aux_char;
									text = realloc(text, (count+1)*sizeof(char));
									res = read(fd, &aux_char, 1);
									count++;
								}
								
								text[count-1] = '#';
								text = realloc(text, (count+1)*sizeof(char));			
																
								res = read(fd, &aux_char, 1);
								while (aux_char != '\n') {
							
									text[count] = aux_char;
									text = realloc(text, (count+1)*sizeof(char));
									res = read(fd, &aux_char, 1);
									count++;
								}
								
								text[count-1] = '#';
								text = realloc(text, (count+1)*sizeof(char));											
								res = read(fd, &aux_char, 1);
								
								while (aux_char != '\n') {
								
									text[count] = aux_char;
									text = realloc(text, (count+1)*sizeof(char));
									res = read(fd, &aux_char, 1);
									count++;
								}
								text[count-1] = '#';
								text = realloc(text, (count+1)*sizeof(char));											
								res = read(fd, &aux_char, 1);
								while (res != 0 && aux_char != '\n') {//while (res != 0 && aux_char != '\0') {
									
									text[count] = aux_char;
									text = realloc(text, (count+1)*sizeof(char));
									res = read(fd, &aux_char, 1);
									count++;
								}
								
								text[count] = '>';
								text = realloc(text, (count+1)*sizeof(char));
								text[count+1] = '\0';
						
								
								/*sprintf(auxString, "%s\n", df->nomFitx);
								write(1, auxString, strlen(auxString));*/
								sprintf(auxString, "%s\n", text);
								write(1, auxString, strlen(auxString));
								count = 0;								
								//enviem abans d'esborrar								
								type = 'D';
								tramaOut = prepararTrama(type, text);
								sprintf(auxString, "Sending data...\n");
								write(1, auxString, strlen(auxString));
								free(text);
								text = NULL;
								Tenviat = EnviarTrama(id_socket, tramaOut);								
								close (fd);
								//borrem fitxer
								numReal = numf - 2;					
								
								sprintf(auxString, "Data sent\n");
								write(1, auxString, strlen(auxString));
								//borrem el fitxer
								if (ty == df->tipus){
									status = remove(aux1);
								}
								//free(aux1);
								//aux1 = NULL;
								if (status == 0){
									/*bytes = sprintf(buff, "%s File deleted successfully %d., crido des de el tipus: %c\n", df->nomFitx, status, ty); 
									write(1, buff, bytes);*/
								}else{			
									bytes = sprintf(buff, "Unable to delete the file %d\n",status); 
									write(1, buff, bytes);
								}
						}
						
						
						
						if (ty == 'i' && df->nomFitx[llargadaNomFitxer-1] == 'g' && df->nomFitx[llargadaNomFitxer-2] == 'p' && df->nomFitx[llargadaNomFitxer-3] == 'j' && df->nomFitx[llargadaNomFitxer-4] == '.'){
							
							sprintf(auxString, "File name: %s\n", df->nomFitx);
							write(1, auxString, strlen(auxString));
							
							df->tipus = 'i';
							
							textImatge = NULL;
							textImatge = malloc(sizeof(char));	
							/*char * dadesImatge;
							
							dadesImatge = NULL;
							dadesImatge = malloc(sizeof(char));*/
							
							
							char caracter;
							//unsigned long resJpg = 0;
							int resJpg = 0;
							int ret = 0;
							
							
							fd = open(aux1, O_RDONLY);
							if (fd <= 0){
								sprintf(auxString, "Error opening file\n");
								write(1, auxString, strlen(auxString));
								return 0;
								
							}							
							
							while ((ret = read(fd, &caracter, 1)) > 0) {
								//dadesImatge[resJpg] = caracter;
								//printf("%c", caracter);
								//dadesImatge = realloc(dadesImatge, (resJpg+1)*sizeof(char));	
								resJpg++; 
							}
							
							close (fd);
							
							count = 0;
							//printf("Resolució: %d, and ret: %d\n", resJpg, ret);
							textImatge[count] = '<';
							textImatge = realloc(textImatge, (count+1)*sizeof(char));
							count++;
							
							//printf("nom fitxer\n");
							int j = 0;
							while (df->nomFitx[j] != '\0') {
								
								textImatge[count] = df->nomFitx[j];
								textImatge = realloc(textImatge, (count+1)*sizeof(char));
								j++;
								count++;
							}
							textImatge[count] = '#';
							count++;
							textImatge = realloc(textImatge, (count+1)*sizeof(char));
							
							
							char buffer[40];
							
							char * mida = itoa(resJpg, buffer, 10);
							j = 0;
							
							while (mida[j] != '\0') {
								
								textImatge[count] = mida[j];
								textImatge = realloc(textImatge, (count+1)*sizeof(char));
								j++;
								count++;
							}
							
							textImatge[count] = '#';
							count++;

							int fd_p[2];
							char *args[] = { "md5sum", aux1, NULL};
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
							wait(NULL);
							waitpid(pid, NULL, 0);
							
							j = 0;
							textImatge = realloc(textImatge, (count+4)*sizeof(char));
							while (stringmd5sum[j] != '\0') {//while (res != 0 && aux_char != '\0') {
								
								textImatge[count] = stringmd5sum[j];
								textImatge = realloc(textImatge, (count+2)*sizeof(char));
								//res = read(fd, &aux_char, 1);
								j++;
								count++;
							}
							
							
							free(stringmd5sum);
							stringmd5sum = NULL;
							
							textImatge = realloc(textImatge, (count+1)*sizeof(char));
							textImatge[count] = '>';	
							count++;
							textImatge = realloc(textImatge, (count+1)*sizeof(char));
							textImatge[count] = '\0';
							//printf("String: %szz\n", textImatge);
							
														
							type = 'I';
							tramaOut = prepararTrama(type, textImatge);
							Tenviat = EnviarTrama(id_socket, tramaOut);
							
							
							char * strDadesImUnaTrama;
							
							strDadesImUnaTrama = NULL;
							strDadesImUnaTrama = malloc(sizeof(char)*(100));

							long long numTrames = resJpg / 100;
							long long resid = resJpg % 100;
							long long ix = 0;
							long long iImatge = 0;
							long long iImatgeTram = 0;
							
							
							//resJpg = 0;
							ret = 0;
							
							//printf("NOM ARXIUUUU: %s\n", aux1);
							
							fd = open(aux1, O_RDONLY);
							if (fd <= 0) return 0;
							
							
							//Enviem totes les trames de les dades de la imatge
							while (ix <= numTrames){
								iImatgeTram = 0;		
								while (iImatgeTram < 100 &&  iImatge <= (resJpg + resid)){
									read(fd, &caracter, 1);
									strDadesImUnaTrama[iImatgeTram] = caracter;//dadesImatge[iImatge];
									//printf("%c", strDadesImUnaTrama[iImatgeTram]);
									iImatge++;
									iImatgeTram++;
								}
								type = 'F';
								
								tramaOut = prepararTrama(type, strDadesImUnaTrama);

								Tenviat = EnviarTrama(id_socket, tramaOut);	
								
								ix++;
							}
							free(textImatge);
							textImatge = NULL;	
							free(strDadesImUnaTrama);
							strDadesImUnaTrama = NULL;
							
							close (fd);
							
							//borrem fitxer
							numReal = numf - 2;					
							//printf("---%s.\n", aux1); 
							//borrem el fitxer
							if (ty == df->tipus){
								status = remove(aux1);
							}
							//free(aux1);
						
							if (status == 0){
								/*bytes = sprintf(buff, "%s file deleted successfully %d., crido des de el tipus: %c\n", df->nomFitx, status, ty); 
								write(1, buff, bytes);*/
							}else{			
								bytes = sprintf(buff, "Unable to delete the file %d\n",status); 
								write(1, buff, bytes);
							}
						}
						
				}else{
					//Enviem missatge test
					type = 'T';
					tramaOut = prepararTrama(type, "Test");
					Tenviat = EnviarTrama(id_socket, tramaOut);	
					
					
				}
			}
			bytes = sprintf(buff, "\n\n"); 
			write(1, buff, bytes);
			
			closedir (dir);	  
			return 1;
}



char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
