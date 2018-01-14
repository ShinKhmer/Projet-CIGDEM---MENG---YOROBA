// GTK Function


//Bouton Commencez
static void activate (GtkApplication* app,gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;
  int status;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Bienvenue chez CigMenYo");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show_all (window);
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Commencez");
  gtk_container_add (GTK_CONTAINER (button_box), button);
  gtk_widget_show_all (window);

return status;
}
