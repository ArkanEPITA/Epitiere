# ifndef GTKU_H_
# define GTKU_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <gtk/gtk.h>



typedef struct {
	gpointer user_data;
	GtkBuilder* builder;
}Data;




//void create_window(int argc, char* argv[]);

#endif
