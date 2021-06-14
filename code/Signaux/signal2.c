#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 2

//definition of the different options for our coffee machine
char * help[]    = {"echo", "Chose your function\n0-help\n1-start\n2-stop\n3-status\n==========\n\n", NULL};
char * start[]   = {"echo", "start machine\n", NULL};
char * stop[]    = {"echo", "stop machine\n", NULL};
char * status[]  = {"echo", "machine status\n", NULL};

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

//Used to capture the program close request signal
void sigint_handler(int sig) {
    static int countdown = 2;
    countdown--;
    if (countdown > 0 )
        warnx("Please insist %d more time(s)", countdown);
    else {
        warnx("Ok, exiting");
        _exit(sig);
    }
}

int main() //program which takes a character string as input
{
    char buffer[BUFFER_SIZE];
    // Install signal handler
    signal(SIGINT, sigint_handler);
    ssize_t r = 1;
    printf("Chose your function\n0-help\n1-start\n2-stop\n3-status\n==========\n\n");

    //STDIN_FILENO corresponds to the file descriptor of the input it will be changed in the future
    while((r = read(STDIN_FILENO,&buffer,7)))
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
        if(strcmp(str,"help") == 0)
        {
            Fonction(help);
            continue;
        }
        else if(strcmp(str,"start") == 0)
            Fonction(start);
        else if(strcmp(str,"stop") == 0)
            Fonction(stop);
        else if(strcmp(str,"status") == 0)
            Fonction(status);
        else
            Fonction(help);
        free(str);
    }

  return 0;
}