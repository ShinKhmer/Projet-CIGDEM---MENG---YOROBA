// PROTOTYPES
void createWinGTK(GtkWidget *window);
void button_action (GtkWidget *widget,gpointer data,MYSQL *db,int tabplat[][2],int id_button);
void apply_button(GtkWidget *button,GtkWidget *image,GtkWidget *array;);
void button_reset (GtkWidget *widget,gpointer data,int **tabplat);
void button_order (GtkWidget *widget,gpointer data);
//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

void button_action (GtkWidget *widget,gpointer data,MYSQL *db,int tabplat[][2],int id_button)
{
  g_print ("\nAction Bouton\n");
  tabplat[id_button][1]+=1;
  g_print ("valeur de tab[%d][%d] TEST \n",id_button,tabplat[id_button][1]);

  //char update[200] = "UPDATE INGREDIENT SET quantity = quantity - 1 WHERE name = 'pork'";
  //g_print ("%c",update);
  //mysql_query(db,update);
}
void button_reset (GtkWidget *widget,gpointer data,int **tabplat)
{
    int i = 0;
    for (i=0;i<13;i++){
       tabplat[i][1] = 0;
    }
}

void button_order (GtkWidget *widget,gpointer data)
{

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
