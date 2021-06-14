# ifndef INTERFACE_H_
# define INTERFACE_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <gtk/gtk.h>



typedef struct {
	gpointer user_data;
	GtkBuilder* builder;
}Data;

char* client();

#endif
