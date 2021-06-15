#include "interface.h"



struct GetVal{
  GtkSpinButton *hours;
  GtkSpinButton *minutes;
  char* type;
  };

struct GetVal Value;
int sockfd;


void create_window(int argc, char* argv[], char* json_file)
{

  //printf("json file : %s\n", json_file);
  //Init variables
  GtkWidget *main_window;
  Data data;


  //Init GTK
  gtk_init(&argc, &argv);


  //Build from .glade
  data.builder = gtk_builder_new();
  gtk_builder_add_from_file(data.builder, "cafetiere.glade", NULL);

	//Get the objects
	main_window =  GTK_WIDGET(gtk_builder_get_object(data.builder, "main_window"));
  GtkSpinButton *spinbuttonHours = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonHours"));
  GtkSpinButton *spinbuttonMinutes = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonMinutes"));
  GtkToggleButton *shortButton = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data.builder, "Short"));
  GtkToggleButton *longButton = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data.builder, "Long"));




  //link w/ css file
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);


  char coffees[30][6];
  for (int i = 0; i < 30; ++i)
  {
      memset(coffees[i], 0, 6);
  }
  int posCoffee = 0;
  int c = 0;
  int posc = 0;

  /*char tmp[5];
  memset(tmp, 0, 5);*/

  while(posCoffee < 30)
  {
    //printf("%c\n", json_file[c]);
    if(json_file[c] == '\n')
    {
      posc = 0;

      //printf("%s\n", coffees[posCoffee]);
      posCoffee++;
    }
    else
    {
      coffees[posCoffee][posc] = json_file[c];
      posc++;
    }
    c++;
  }

  
  for(int i = 0; i < 30; i++)
  {
    printf("%s\n", coffees[i]);
  }





  char* type = calloc(5, sizeof(char));
  type = coffees[0];
  char* time = calloc(4, sizeof(char));
  time = coffees[1];
  char* activate = calloc(1, sizeof(char));
  activate = coffees[2];

  printf("\ntime = %s\ntype = %s\nactivate = %s\n", time, type, activate);
  //printf("coffees[0] = %s\n", coffees[0]);

  char* h = calloc(2, sizeof(char));
  strncpy(h, time, 2);

  char* min = calloc(2, sizeof(char));
  strncpy(min, time+2, 2);


  //printf("%s:%s\n", h, min);


  //Set the value of the spinbuttonHours to hours
  int hours = atoi(h);
  gtk_spin_button_set_value(spinbuttonHours, hours);

  //Set the value of the spinbutton2 to minutes
  int minutes = atoi(min);
  gtk_spin_button_set_value(spinbuttonMinutes, minutes);


  int ret1 = strncmp(type, "long", 4);
  int ret2 = strncmp(type, "court", 5);


  if(ret1 == 0)
  {
    printf("LONG\n");
    gtk_toggle_button_set_active(longButton, TRUE);
  }
  else if(ret2 == 0)
  {
    printf("SHORT\n");
    gtk_toggle_button_set_active(shortButton, TRUE);
  }




  Value.hours = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonHours"));
  Value.minutes = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonMinutes"));
  Value.type = "short";

	//Connect signals
	gtk_builder_connect_signals(data.builder, &data);

  gtk_window_set_title(GTK_WINDOW(main_window), "Epitière");
  gtk_widget_show_all(main_window);
  gtk_main();
}


char* client_mover()
{
  Client cli = client();
  sockfd = cli.sockfd;
  return cli.json_file;
}


int main(int argc, char* argv[])
{
  char* json_file = client_mover();
  create_window(argc, argv, json_file);

  return EXIT_SUCCESS;
}


void on_validation_clicked()
{
  int hours = gtk_spin_button_get_value_as_int(Value.hours);
  int minutes = gtk_spin_button_get_value_as_int(Value.minutes);

  printf("Time set to %d:%d\n", hours, minutes);
  printf("You will get a %s coffee\n", Value.type);
}

void on_Short_toggled()
{
  Value.type = "short";
}

void on_Long_toggled()
{
  Value.type = "long";
}

// called when window is closed
void on_main_window_destroy()
{
  close(sockfd);
  gtk_main_quit();
}