#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typedef struct User
{
	char nom[30];
	int age;
}User;*/
char buffer[32] = "Bonjour !";

int main(void)
{

int socketServer = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in addrServer;
addrServer.sin_addr.s_addr = inet_addr("10.0.2.15");
addrServer.sin_family = AF_INET;
addrServer.sin_port = htons(23);

bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));
printf("bind : %d\n",socketServer);

listen(socketServer, 5);
printf("Patientez pendant que le client se connecte sur le port 23...\n"); 

struct sockaddr_in addrClient;
socklen_t csize = sizeof(addrClient);
int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
printf("accept\n");

printf("client : %d\n",socketClient);

/*User user = {
	.nom = "Clara",
	.age = 20
	
};*/

send(socketClient,buffer,32,0);

close(socketClient);
close(socketServer);
return 0;
}
