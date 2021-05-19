#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define RASPBERRY "1aA"
#define API "0zZ"

typedef struct ClientRaspApi 
  {
    int acc;
    int api;
    int rasp;
  } ClientRaspApi;

// Function designed for chat between client and server.
void* func(void* structs)
{
	
	ClientRaspApi* RaspApi = structs;
	char buff[MAX];
	int sockfd = RaspApi->acc;

	read(sockfd, buff, sizeof(buff));
	write(RaspApi->rasp,buff,sizeof(buff));
	printf("Get to the API client : %d\n", sockfd);
	
	close(sockfd);
	pthread_exit(NULL);
}

void* GetApi(void* RaspApis)
{
  ClientRaspApi* RaspApi = RaspApis;
  char buff[MAX];
  int afd = RaspApi->api;
  int sockfd = RaspApi->acc;
  bzero(buff, sizeof(buff));
  // infinite loop for chat
  //printf("acc = %d\nrasp = %d\napi = %d\n",RaspApi->acc, RaspApi->rasp, RaspApi->api);
  
  for (;;) 
  {
    
    if(read(sockfd, buff, sizeof(buff)) != 0)
    {

      write(afd, buff, sizeof(buff));
      //faire le GET à l'API
    }

  }
  close(sockfd);
  pthread_exit(NULL);
}

void* PostRasp(void* RaspApis)
{
  ClientRaspApi* RaspApi = RaspApis;
  char buff[MAX];
  int sockfd = RaspApi->acc;
  bzero(buff, sizeof(buff));
  // infinite loop for chat
  for (;;) 
  {
    read(sockfd, buff, sizeof(buff));
  }
  close(sockfd);
  pthread_exit(NULL);
}


// Driver function
int main()
{
  
  ClientRaspApi* RaspApi = malloc(sizeof(ClientRaspApi));
  
  RaspApi->rasp= -1;
  RaspApi->acc = -1;

  char buff[1];
  int sockfd, connfd;
  //socklen_t len;
  struct sockaddr_in servaddr;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("10.0.2.15");
  servaddr.sin_port = htons(PORT);
  int value = 1;

  if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&value,sizeof(int)) < 0)
    errx(EXIT_FAILURE,"Fail reusing the same address");
  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
    printf("socket bind failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully binded...\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  }
  else
    printf("Server listening...\n");
  
  pthread_t tid[60];
  int i = 0;
  while(1)
  {

    //len = sizeof(cli);
    // Accept the data packet from client and verification
    connfd = accept(sockfd, NULL, NULL);
    
    if (connfd < 0) {
      printf("server acccept failed...\n");
      exit(0);
    }
    else
      printf("server acccept connexion...\n");

    // vérifie si le client est l'api ou le raspberry
    read(connfd, buff, sizeof(buff));
    if(strncmp(RASPBERRY, buff,1) == 0)
    {
    	printf("server acccept the Raspberry...\n");
      RaspApi->rasp = connfd;
      if( pthread_create(&tid[i++], NULL, PostRasp, RaspApi) != 0)
        errx(EXIT_FAILURE, "Cannot create a thread...");
    }
    else
    {
    	printf("server acccept the client...\n");
      RaspApi->acc = connfd;
      if( pthread_create(&tid[i++], NULL, func, RaspApi) != 0)
        errx(EXIT_FAILURE, "Cannot create a thread...");

      if( i >= 50)
      {
        i = 0;
        while(i < 51)
        {
          pthread_join(tid[i++],NULL);
        }
        i = 0;
      }
    }
  }

  // After chatting close the socket
  close(sockfd);
}
