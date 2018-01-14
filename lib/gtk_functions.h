// PROTOTYPES
void createWinGTK(GtkWidget *window);
static void print_hello (GtkWidget *widget,gpointer data,MYSQL *db);
//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

static void print_hello (GtkWidget *widget,gpointer   data,MYSQL *db)
{
  g_print ("Hello World\n");
  char update[200] = "UPDATE INGREDIENT SET quantity = quantity - 1 WHERE name = 'salmon'";
  mysql_query(db, update);
}
