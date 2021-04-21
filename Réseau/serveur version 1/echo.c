#include <stdlib.h>
#include <unistd.h>
#include <err.h>

#define BUFFER_SIZE 512

void rewrite(int fd, const void *buf, size_t count)
{
    size_t fcount = 0;
	ssize_t err = 0;
	while (fcount < count)
	{
		err = write(fd, buf, count);
		if(err == -1)
			errx(EXIT_FAILURE,"an error occurs");
		fcount += err;
		count -= err;
	}
}

void echo(int fd_in, int fd_out)
{
	ssize_t r;
	void* buf = malloc(BUFFER_SIZE);
    while(1)
    {
    	r = read(fd_in, buf, BUFFER_SIZE);
    	if(r == -1)
    	{
    		err(3, "error in read");
    	}
    	if(r == 0)
    	{
    		break;
    	}
    	rewrite(fd_out, buf, r);
    }
    
}