#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

#define MAXI 200
#define PORT 8080
#define SA struct sockaddr


//Get what the server sent to the client
char* get_buffer(int sockfd)
{
  write(sockfd, "1", 1);
  char buff[MAXI];
  ssize_t r = 0;

  memset(buff, 0, MAXI);

  ssize_t buff_size = 0;;
  while(r == 0)
  {

      r = read(sockfd, &buff, sizeof(buff));
      
      buff_size += r;
      sleep(1);
  }

  char* res = calloc(buff_size, sizeof(char));
  for (ssize_t i = 0; i < buff_size; ++i)
  {
  	res[i] = buff[i];
  }

  return res;
}


//Take care of the connection with the server
//And send the scket and the message written by the server to
//Interface.c
Client client()
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
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  char* json_file = get_buffer(sockfd);

  Client cli = { sockfd, json_file };

  return cli;
}
