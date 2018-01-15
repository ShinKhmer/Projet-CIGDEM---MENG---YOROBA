//Structure de la COMBOBOX
typedef struct
{
   gint     index;
   gchar *  p_text;
}
combo_data_st;
// PROTOTYPES
void createWinGTK(GtkWidget *window);
void button_action (GtkWidget *widget,MYSQL *db,int tabplat[][2],int id_button);
void apply_button(GtkWidget *button,GtkWidget *image,GtkWidget *array;);
void button_reset (GtkWidget *widget,gpointer data,int **tabplat);
void button_order (GtkWidget *widget,gpointer data,MYSQL *db, MYSQL_RES *res, MYSQL_ROW row);
static combo_data_st get_active_data (GtkComboBox * p_combo);
static void cb_show (GtkWidget * p_wid, gpointer p_data);


//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

void button_action (GtkWidget *widget,MYSQL *db,int tabplat[][2],int id_button)
{
  g_print ("\nAction Bouton\n");
  tabplat[id_button][1]++;
  g_print ("valeur de tab[%d][1] TEST  vaut %d commandes \n",id_button,tabplat[id_button][1]);

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

void button_order (GtkWidget *widget,gpointer data,MYSQL *db, MYSQL_RES *res, MYSQL_ROW row)
{
// CREATION DE LA FACTURE

// Récuperation de l'id terminal
/*
    sprintf(request,"SELECT id_terminal FROM terminal WHERE id_terminal='%d'",id_terminal);
    mysql_query(mysql,request);
    // Result recuperation
    res = mysql_use_result(mysql);
    row = mysql_fetch_row(result);
    mysql_free_result(result);

    // Récupération numéro de commande

    sprintf(request,"SELECT id_order FROM order WHERE id_terminal='%d'",id_terminal);
        mysql_query(mysql,request);
        // Result recuperation
        res = mysql_use_result(mysql);
        row = mysql_fetch_row(result);
        mysql_free_result(result);

// Récupération total de la commande

     sprintf(request,"SELECT id_order FROM order WHERE total_price='%d'",total_price);
            mysql_query(mysql,request);
            // Result recuperation
            res = mysql_use_result(mysql);
            row = mysql_fetch_row(result);
            mysql_free_result(result);

    FILE *fact = fopen("facture.txt","a+t");
    int word = 0;

    if(fact == NULL) {
        EXIT_SUCCESS

    }
    while ((word = fgetc(fact)) != EOF ) {

            printf ("%c",word)

    }
    fclose(fact)
    */
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

/* Fonction qui recupere les donnees de l'element courant affiche. sur la combo BOX Sur place ou a emporter*/
static combo_data_st get_active_data (GtkComboBox * p_combo)
{
   GtkTreeModel   *  p_model = NULL;
   GtkTreeIter       iter;
   combo_data_st     p_st;


   /* On recupere le modele qu'on a cree. */
   p_model = gtk_combo_box_get_model (p_combo);

   /* On recupere le GtkTreeIter de l'element courant. */
   if (gtk_combo_box_get_active_iter (p_combo, & iter))
   {
      /*
       * On recupere les donnees de l'element courant a savoir
       * un entier et une chaine de caracteres.
       */
      gtk_tree_model_get (
         p_model,
         & iter,
         0, & p_st.index,
         1, & p_st.p_text,
         -1
      );
   }
    return p_st;
}

/*
 * Callback des GtkButton.
 */
static void cb_show (GtkWidget * p_wid, gpointer p_data)
{
   GtkComboBox    *  p_combo  = p_data;
   combo_data_st     p_st;


   p_st = get_active_data (p_combo);
   g_printf ("Element courant : %d%s\n", p_st.index, p_st.p_text);


   (void) p_wid;
}
