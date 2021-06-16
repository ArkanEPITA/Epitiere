#include "interface.h"



struct GetVal{
  GtkSpinButton *hours;
  GtkSpinButton *minutes;
  GtkToggleButton *shortButton;
  GtkToggleButton *longButton;
  GtkToggleButton *enableButton;
  GtkToggleButton *disableButton;
  GtkComboBox *comboboxCoffee;
  };

struct GetVal Value;

int sockfd;
char list[30][6];


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
  GtkToggleButton *enableButton = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data.builder, "radiobuttonEnabled"));
  GtkToggleButton *disableButton = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data.builder, "radiobuttonDisabled"));
  GtkComboBox *coffeeEntry = GTK_COMBO_BOX(gtk_builder_get_object(data.builder, "coffeeChooser"));
  //GtkEntry *entry = GTK_ENTRY(gtk_builder_get_object(data.builder, "entry"));
  
/*
  GtkEntry *coffee1 = gtk_combo_box_get_active(coffeeEntry);
  printf("entry1 = %s\n", gtk_entry_get_text(coffee1));
*/
  Value.hours = spinbuttonHours;
  Value.minutes = spinbuttonMinutes;
  Value.shortButton = shortButton;
  Value.longButton = longButton;
  Value.enableButton = enableButton;
  Value.disableButton = disableButton;
  Value.comboboxCoffee = coffeeEntry;


  //link w/ css file
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);




  for (int i = 0; i < 30; ++i)
  {
      memset(list[i], 0, 6);
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

      //printf("%s\n", list[posCoffee]);
      posCoffee++;
    }
    else
    {
      list[posCoffee][posc] = json_file[c];
      posc++;
    }
    c++;
  }

  
/*

  for(int i = 0; i < 30; i++)
  {
    printf("%s\n", list[i]);
  }

*/


  char* type = calloc(5, sizeof(char));
  type = list[0];
  char* time = calloc(4, sizeof(char));
  time = list[1];
  char* activate = calloc(1, sizeof(char));
  activate = list[2];

  //printf("\ntime = %s\ntype = %s\nactivate = %s\n", time, type, activate);
  //printf("list[0] = %s\n", list[0]);

  char* h = calloc(2, sizeof(char));
  strncpy(h, time, 2);

  char* min = calloc(2, sizeof(char));
  strncpy(min, time+2, 2);


  //printf("%s:%s\n", h, min);

  //Set the active id
  gtk_combo_box_set_active_id(coffeeEntry, "0");


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
    gtk_toggle_button_set_active(longButton, TRUE);
  }
  else if(ret2 == 0)
  {
    gtk_toggle_button_set_active(shortButton, TRUE);
  }


  int act = atoi(activate);
  if(act == 0)
  {
    gtk_toggle_button_set_active(disableButton, TRUE);
  }
  else
  {
    gtk_toggle_button_set_active(enableButton, TRUE);
  }




  //Color the entry of the combobox
/*
  GtkStyleContext *context;
  context = gtk_widget_get_style_context(main_window);
  gtk_style_context_add_class(context,"enter_button");
*/



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
  char* id = (char*)gtk_combo_box_get_active_id(Value.comboboxCoffee);
  int active;
  char* type;

  gboolean act = gtk_toggle_button_get_active(Value.enableButton);
  if(act)
  {
    active = 1;
  }
  else
  {
    active = 0;
  }

  gboolean typ = gtk_toggle_button_get_active(Value.shortButton);
  if(typ)
  {
    type = "court";
  }
  else
  {
    type = "long";
  }

  char* res = calloc(15, sizeof(char));

/*
  printf("id = %s\n", id);
  printf("active = %d\n", active);
  printf("type = %s\n", type);
  printf("time = %d", hours);
  printf("%d\n\n", minutes);
*/


  sprintf(res, "%s\n%d\n%s\n%d%02d", id, active, type, hours, minutes);
  
  write(sockfd, res, strlen(res));
}


// called when window is closed
void on_main_window_destroy()
{
  write(sockfd, "closed", 6);
  close(sockfd);
  gtk_main_quit();
}


void on_coffeeChooserEntry_changed()
{
  char* id = (char*)gtk_combo_box_get_active_id(Value.comboboxCoffee);
  int pos = atoi(id);

  char* type = calloc(5, sizeof(char));
  type = list[pos*3];
  char* time = calloc(4, sizeof(char));
  time = list[pos*3+1];
  char* activate = calloc(1, sizeof(char));
  activate = list[pos*3+2];

  //printf("\ntime = %s\ntype = %s\nactivate = %s\n", time, type, activate);
  //printf("list[0] = %s\n", list[0]);

  char* h = calloc(2, sizeof(char));
  strncpy(h, time, 2);

  char* min = calloc(2, sizeof(char));
  strncpy(min, time+2, 2);




  //Set the value of the spinbuttonHours to hours
  int hours = atoi(h);
  gtk_spin_button_set_value(Value.hours, hours);

  //Set the value of the spinbutton2 to minutes
  int minutes = atoi(min);
  gtk_spin_button_set_value(Value.minutes, minutes);


  int ret1 = strncmp(type, "long", 4);
  int ret2 = strncmp(type, "court", 5);

  if(ret1 == 0)
  {
    gtk_toggle_button_set_active(Value.longButton, TRUE);
  }
  else if(ret2 == 0)
  {
    gtk_toggle_button_set_active(Value.shortButton, TRUE);
  }


  int act = atoi(activate);
  if(act == 0)
  {
    gtk_toggle_button_set_active(Value.disableButton, TRUE);
  }
  else
  {
    gtk_toggle_button_set_active(Value.enableButton, TRUE);
  }

}