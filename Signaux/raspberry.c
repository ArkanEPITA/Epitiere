#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFFER_SIZE 20

char * longcoffe[]   = {"echo", "longcoffe \n", NULL};
char * shortcoffe[]  = {"echo", "shortcoffe\n", NULL};

//function that calls a command with the user request as a parameter
void Fonction(char ** arg)
{
    if (fork()) 
    { // parent process
        wait(NULL); 
    }
    else 
    { // child process
        printf("%s\n", arg[1]);
        if(execvp(arg[0], arg))
            errx(EXIT_FAILURE,"command fail");
    }
}

int main(int fd) //program which takes a character string as input
{
    char buffer[BUFFER_SIZE];

/*  ===================================
                server part
    ===================================*/

    struct addrinfo hints;
    struct addrinfo *rp;
    struct addrinfo *result;
    int addrinfo_error;
    

    const char *port = "80";
    

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4 only
    hints.ai_socktype = SOCK_STREAM; // TCP
    
    // Get your info
    addrinfo_error = getaddrinfo(host, port,&hints,&result);

    // Error management
    if(addrinfo_error !=0)
    {errx(EXIT_FAILURE,"Fail getting address for %s on port %s: %s",host, port, gai_strerror(addrinfo_error));}

    // result points to a linked list
    // try to connect f
    
    int cnx = -1;
    for(rp = result; rp !=NULL; rp = rp->ai_next)
    {

        cnx = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if(cnx ==-1)
            continue;
        if(connect(cnx, rp->ai_addr, rp->ai_addrlen)!=-1)
            break;
        close(cnx);
    }

    free(result);

    if(rp ==NULL)
        errx(EXIT_FAILURE,"Couldn't connect\n");



/*  ===================================
                coffe part
    ===================================*/

    ssize_t r = 1;
    while((r = read(cnx,buffer,7)))
    {
        if(r == -1)
            errx(EXIT_FAILURE,"Couldn't read the input\n");
        char *str = calloc(sizeof(char),(r));

        //store the user request in a buffer
        for (int i = 0; i < r-1; ++i)
        {
            str[i] = buffer[i];
        }
        //calls the function according to the requested character string
        if(strcmp(str,"longcoffe") == 0)
        {
            write(cnx,"not_ok",6);
            Fonction(longcoffe);
            sleep(180);
            write(cnx,"ok",2);
        }
        else if(strcmp(str,"shortcoffe") == 0)
        {
            write(cnx,"not_ok",6);
            Fonction(shortcoffe);
            sleep(120);
            write(cnx,"ok",2);
        }
        else
            Fonction(help);
        free(str);
    }
    
    close(cnx);
}