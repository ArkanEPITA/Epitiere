#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 2

char * help[]    = {"echo", "Chose your function\n0-help\n1-start\n2-stop\n3-status\n4-connard\n==========\n\n", NULL};
char * start[]   = {"echo", "start machine\n", NULL};
char * stop[]    = {"echo", "stop machine\n", NULL};
char * status[]  = {"echo", "machine status\n", NULL};
char * connard[] = {"echo", "ptdr je sais pas\n", NULL};

void sigint_handler(int sig) {
    static int countdown = 2;

    countdown--;
    pid_t pid = getpid();
    //printf("%d\n",pid );
    if (countdown > 0 )
        warnx("Please insist %d more time(s)", countdown);
    else {
    	
        warnx("Ok, exiting");
        _exit(sig);
    }
}
void Fonction(char ** arg)
{
    if (fork()) 
	{ // parent process
	    wait(NULL);	
  	}
  	else 
  	{ // child process
  		if(execvp(arg[0], arg))
			errx(EXIT_FAILURE,"command fail");
	}
}

int main()
{
	char buffer[BUFFER_SIZE];
	// Install signal handler
    signal(SIGINT, sigint_handler);

	printf("Chose your function\n0-help\n1-start\n2-stop\n3-status\n4-connard\n==========\n\n");
    
    ssize_t r = 1;
    
	while(r = read(STDIN_FILENO,&buffer,1))
    {
    	if(r == -1)
    		errx(EXIT_FAILURE,"Couldn't read the input\n");

    	switch(buffer[0])
	    {
	    	case '0':
	    		Fonction(help);
	    		break;
	    	case '1':
	    		Fonction(start);
	    		break;
	    	case '2':
	    		Fonction(stop);
	    		break;
	    	case '3':
	    		Fonction(status);
	    		break;
	    	case '\n':
	    		break;
	    	default:
	    		printf("Sorry retry or enter 0 for help\n\n");
	    }	
    }	

  return 0;
}