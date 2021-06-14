#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
  write(sockfd, "1", 1);
  char buff[MAX];
  ssize_t r = 0;
  while(r == 0)
  {
      memset(buff,0,MAX);
      ssize_t r = 0;
      r = read(sockfd, buff, sizeof(buff));
      if(r != 0)
      {   
          write(STDOUT_FILENO, buff, r);
          printf("\n");
      }
      sleep(1);
  }

  int n = 0;
  
  memset(buff,0,MAX);
  printf("Enter the string : ");
  while ((buff[n++] = getchar()) != '\n');
  write(sockfd, buff, sizeof(buff));

  printf("From Server : %s", buff);
  
}

int main()
{
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
  servaddr.sin_addr.s_addr = inet_addr("192.168.0.36");
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");
  //write(sockfd,"1",1);
  // function for chat
  func(sockfd);

  // close the socket
  close(sockfd);
}
