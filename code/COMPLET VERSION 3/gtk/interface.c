#include "interface.h"



struct GetVal{
  GtkSpinButton *hours;
  GtkSpinButton *minutes;
  char* type;
  };

struct GetVal Value;



int main(int argc, char* argv[])
{



  //Init variables
  GtkWidget *main_window;
  Data data;


  //Init GTK
  gtk_init(&argc, &argv);


  //Build from .glade
  data.builder = gtk_builder_new();
  gtk_builder_add_from_file(data.builder, "cafetiere.glade", NULL);

	//Get main_window
	main_window =  GTK_WIDGET(gtk_builder_get_object(data.builder, "main_window"));
  //main_window =  GTK_WIDGET(gtk_builder_get_object(data.builder, "main_window"));


  //link w/ css file
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);





/*
  //Get the list of the coffee with the API
  //TODO
  
  //Set the value of the spinbutton1 to hours
  int hours = 5;

  GtkSpinButton *spinbuttonHours = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonHours"));
  gtk_spin_button_set_value(spinbuttonHours, hours);

  char[] request = "GET / HTTP/1.1";


  //Set the value of the spinbutton2 to minutes
  int minutes = 32;
  
  GtkSpinButton *spinbuttonMinutes = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonMinutes"));
  gtk_spin_button_set_value(spinbuttonMinutes, minutes);


  gboolean = gtk_toggle_button_get_active();

  //Set the value of the radio button the the right value
  GtkToggleButton *shortButton = GTK_RADIO_BUTTON(gtk_builder_get_object(data.builder, "Short"));
  gtk_toggle_button_set_active(shortButton, TRUE);

  GtkToggleButton *longButton = GTK_RADIO_BUTTON(gtk_builder_get_object(data.builder, "Long"));
  gtk_toggle_button_set_active(longButton, TRUE); 
*/




  Value.hours = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonHours"));
  Value.minutes = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonMinutes"));
  Value.type = "short";


	//Connect signals
	gtk_builder_connect_signals(data.builder, &data);

  gtk_window_set_title(GTK_WINDOW(main_window), "Epitière");
  gtk_widget_show_all(main_window);
  gtk_main();


  //char* json_file = client();
  //printf("%s\n", json_file);

  return EXIT_SUCCESS;
}


void on_validation_clicked()
{
  int hours = gtk_spin_button_get_value_as_int(Value.hours);
  int minutes = gtk_spin_button_get_value_as_int(Value.minutes);

  printf("Time set to %d:%d\n", hours, minutes);
  printf("You will get a %s coffee\n", Value.type);
  char* json_file = client();
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
void on_window_main_destroy()
{
  gtk_main_quit();
}