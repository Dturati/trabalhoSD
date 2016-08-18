	#include <stdlib.h>
	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
	#include <signal.h>
	#include <sys/wait.h>
	#include <unistd.h>

	#include <pthread.h>

	#define PORTA 2000    
	#define MAXDATASIZE 100 	


	int Meusocket, numbytes;
	char buf[MAXDATASIZE];
	char msg[240];
	struct hostent *he;
	struct sockaddr_in servidor;

	void *ler(void *t);

	int main(int argc, char *argv[])
	{	
		pthread_t thread1;
		pthread_create(&thread1,NULL,ler,NULL);
	
		while(1){
			sleep(1);
			if ((Meusocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
			{
				perror("socket");
				exit(1);
			}


			servidor.sin_family = AF_INET;
			servidor.sin_port = htons(PORTA);
			servidor.sin_addr.s_addr = inet_addr("192.168.4.12");
			bzero(&(servidor.sin_zero), 8);


			if (connect(Meusocket,(struct sockaddr *)&servidor, sizeof(struct sockaddr)) == -1) 
			{
				perror("connect");
				exit(1);
			}
			

				
			if (send(Meusocket,msg, 16, 0) == -1)
			{
				perror("send");
				close(Meusocket);
				exit(0);
			}
			
			if ((numbytes=recv(Meusocket, buf, MAXDATASIZE, 0)) == -1) 
			{
						perror("recv");
						exit(1);
					
			}
			if(buf[0] != '\0'){
				printf("Nova menssagem\n");
				buf[numbytes] = '\0';
				printf("%s",buf);
			}
		
		

	}
	

	return 0;
	
}

/* Ler os dados de entrada */
void *ler(void *t)
{
	
	while(1)
	{
		
		printf("Digite a menssagem\n");
		//scanf("%s",msg);
		fgets(msg,sizeof(msg),stdin);
		strcat(msg, "\n");
		fflush(stdin);
		sleep(1);
		msg[0] = '\0';
	}
}
