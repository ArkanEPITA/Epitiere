# ifndef INTERFACE_H_
# define INTERFACE_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <gtk/gtk.h>
#include <string.h>


//Struct for the gtk builder
typedef struct {
	gpointer user_data;
	GtkBuilder* builder;
}Data;

//Returned structure from the client
typedef struct {
	int sockfd;
	char* json_file;
}Client;


Client client();

#endif
