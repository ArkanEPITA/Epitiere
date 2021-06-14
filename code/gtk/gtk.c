#include "gtku.h"



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

  //Set the value of the spinbutton1 to hours
  int hours = 5;

  GtkSpinButton *spinbutton1 = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbutton1"));
  gtk_spin_button_set_value(spinbutton1, hours);




  //Set the value of the spinbutton2 to minutes
  int minutes = 32;
  
  GtkSpinButton *spinbutton2 = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbutton2"));
  gtk_spin_button_set_value(spinbutton2, minutes);

*/

  Value.hours = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonHours"));
  Value.minutes = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbuttonMinutes"));
  Value.type = "short";


	//Connect signals
	gtk_builder_connect_signals(data.builder, &data);

  gtk_window_set_title(GTK_WINDOW(main_window), "Epitière");
  gtk_widget_show_all(main_window);
  gtk_main();

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
void on_window_main_destroy()
{
  gtk_main_quit();
}