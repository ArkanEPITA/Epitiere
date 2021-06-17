#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void led(char* buff)
{
  
  int pin = 7;
  int time = 15;
  if(wiringPiSetup()==-1)
	{
		exit(0);
	}
	pinMode(pin,OUTPUT);
  
  if(strcmp(buff,"court")==0)
  {
    while(time >=0)
    {
      digitalWrite(pin,1);
      delay(500);
      digitalWrite(pin,0);
      delay(500);
      time--;
    }
  }
  else{
      digitalWrite(pin,1);
      sleep(10);
    }
    digitalWrite(pin,0);
	
}

void func(int sockfd)
{
    char buff[MAX];
    ssize_t r = 0;
    while(1)
    {
        memset(buff,0,5);
        
        
        r = read(sockfd, buff, 5);
        
        if(strcmp(buff, "court") == 0 || strcmp(buff, "long") == 0){
            printf("%s\n", buff);
            led(buff);
        }
       
    }
}

int main()
{
  char buff[NI_MAXHOST];
  int n = 0;
  
  bzero(buff, sizeof(buff));
  printf("Enter the IP server : ");
  while ((buff[n++] = getchar()) != '\n');

  int sockfd;
  struct sockaddr_in servaddr;

  // socket create and varification
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
  servaddr.sin_addr.s_addr = inet_addr(buff);
  //servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  func(sockfd);

  // close the socket
  
}
