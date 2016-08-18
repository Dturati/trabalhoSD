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

#include <pthread.h>

#define MINHAPORTA 2000    /* Porta que os usuarios irão se conectar*/
#define BACKLOG 10     /* Quantas conexões pendentes serão indexadas */
#define MAXDATASIZE 100 

void *ler(void *t);

int Meusocket, Novosocket, numbytes;
struct sockaddr_in meu_endereco;
struct sockaddr_in endereco_dele;
int tamanho;
char msg[100];
char buf[MAXDATASIZE];


int main(int argc, char *argv[])
{
	
	pthread_t thread1;
	pthread_create(&thread1,NULL,ler,NULL);

	if ((Meusocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	meu_endereco.sin_family = AF_INET;
	meu_endereco.sin_port = htons(MINHAPORTA);
	meu_endereco.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(meu_endereco.sin_zero), 8);        

	if (bind(Meusocket, (struct sockaddr *)&meu_endereco, sizeof(struct sockaddr))== -1) 
	{
		perror("bind");
		exit(1);
	}
	
	if (listen(Meusocket, BACKLOG) < 0) 
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{
		tamanho = sizeof(struct sockaddr_in);
		if ((Novosocket = accept(Meusocket, (struct sockaddr *)&endereco_dele,&tamanho)) < 0)
		{
				perror("accept");
				continue;
		}
	

		if ((numbytes=recv(Novosocket, buf, MAXDATASIZE, 0)) == -1)
		{
		    perror("recv");
		    exit(1);
		}

		if(buf[0] != '\0'){
			printf("Nova menssagem\n");
		    buf[numbytes] = '\0';
		    printf("%s", buf);
		}
	
	
		if (send(Novosocket,msg, 16, 0) == -1)
		{
			perror("send");
			close(Novosocket);
			exit(0);
		}

		close(Novosocket);
		while(waitpid(-1,NULL,WNOHANG) > 0);

	}

	return 0;


}


/*Ler dos dados de entrada*/
void *ler(void *t)
{
	
	while(1)
	{
		
		printf("Digite a menssagem\n");
		//scanf("%s",msg);
		fgets(msg,sizeof(msg),stdin);	
		strcat(msg, "\n");
		sleep(1);
		msg[0] = '\0';
	}
}