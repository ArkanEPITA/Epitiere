#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include "echo.h"

int main(int argc, char** argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage:\n"
            "Arg 1 = Port number (e.g. 2048)");
    
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *rp;
	int addrinfo_error;
	int cnx;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	addrinfo_error = getaddrinfo(NULL, argv[1], &hints, &result);
	
	if(addrinfo_error !=0)
	{
		errx(EXIT_FAILURE,"Fail getting address on port %s: %s", argv[1], gai_strerror(addrinfo_error));
	}
	
	for(rp = result; rp !=NULL; rp = rp->ai_next)
	{
		cnx = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if(cnx ==-1)
		{
			continue;
		}
		int value = 1;
		
		int error = setsockopt(cnx, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int));
		
		if(error == -1)
		{
			errx(EXIT_FAILURE, "error while setting option to socket");
		}

		int err_bind = bind(cnx, rp->ai_addr, rp->ai_addrlen);

		if(err_bind == -1)
		{
			close(cnx);
			continue;
		}
		else
		{
			break;
		}
	}
	freeaddrinfo(result);
	if(rp == NULL)
	{
		errx(EXIT_FAILURE, "couldn't connect");
	}

	int err_listen = listen(cnx, 5);

	if(err_listen == -1)
	{
		errx(EXIT_FAILURE, "couldn't listen");
	}

	printf("Server is waiting for connections\n");

	int server = accept(cnx, NULL, NULL);

	if(server == -1)
	{
		errx(EXIT_FAILURE, "couldn't accept");
	}

	printf("connection is a success\n");

	echo(server, server);

	close(cnx);
	close(server);
}