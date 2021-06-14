#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[32] = "";
#define PORT 8080


int main(void)
{

int socketClient = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in addrClient;
addrClient.sin_addr.s_addr = inet_addr("10.0.2.15");
addrClient.sin_family = AF_INET;
addrClient.sin_port = htons(PORT);

connect(socketClient,(const struct sockaddr *)&addrClient,sizeof(addrClient));
printf("connexion\n");

if(recv(socketClient, buffer, 32, 0) != -1){
	printf("Recu : %s\n", buffer);
}
printf("connect\n");
close(socketClient);
return 0;
}
