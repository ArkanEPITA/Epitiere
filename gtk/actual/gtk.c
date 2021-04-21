#include "gtku.h"


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
  GError *error = 0;
  GFile *css_fp = g_file_new_for_path("style.css");

  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  //gtk_style_context_add_provider_for_screen(gdk_display_get_default_screen(gdk_display_get_default()), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_css_provider_load_from_file(cssProvider, css_fp , &error);


  //Set the value of the spinbutton1 to hours
  int hours = 5;

  GtkSpinButton *spinbutton1 = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbutton1"));
  gtk_spin_button_set_value(spinbutton1, hours);

  //Set the value of the spinbutton2 to minutes
  int minutes = 32;
  GtkSpinButton *spinbutton2 = GTK_SPIN_BUTTON(gtk_builder_get_object(data.builder, "spinbutton2"));
  gtk_spin_button_set_value(spinbutton2, minutes);




	//Connect signals
	gtk_builder_connect_signals(data.builder, &data);

  gtk_window_set_title(GTK_WINDOW(main_window), "Epitière");
  gtk_widget_show_all(main_window);
  gtk_main();


  return EXIT_SUCCESS;
}


void print_coucou()
{
  printf("coucou\n");
}

// called when window is closed
void on_window_main_destroy()
{
  gtk_main_quit();
}