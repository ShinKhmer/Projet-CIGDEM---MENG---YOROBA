// PROTOTYPES
void createWinGTK(GtkWidget *window);
static void button_action (GtkWidget *widget,gpointer data,MYSQL *db,int **tabplat);
void apply_button(GtkWidget *button,GtkWidget *image,GtkWidget *array;);
//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

static void button_action (GtkWidget *widget,gpointer   data,MYSQL *db,int **tabplat)
{
  g_print ("\nAction Bouton\n");
  tabplat[0][0]+=1;
  char update[200] = "UPDATE INGREDIENT SET quantity = quantity - 1 WHERE name = 'pork'";
  mysql_query(db, update);
}
/*
void apply_button(GtkWidget *button,GtkWidget *image,GtkWidget *array;)
{
gtk_table_attach(GTK_TABLE(array), button, 0, 1, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
gtk_container_add (GTK_CONTAINER (button), image);
gtk_button_set_image_position (button,GTK_POS_BOTTOM);
gtk_button_set_image (button,image);
}
*/
