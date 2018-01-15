// PROTOTYPES
void createWinGTK(GtkWidget *window);
void button_action (GtkWidget *widget,MYSQL *db,int tabplat[][2],int id_button);
void apply_button(GtkWidget *button,GtkWidget *image,GtkWidget *array;);
void button_reset (GtkWidget *widget,gpointer data,int **tabplat);
void button_order (GtkWidget *widget,gpointer data,MYSQL *db, MYSQL_RES *res, MYSQL_ROW row);


// STRUCTURES
typedef struct db_params{
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int test;
}db_params;


//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

void test(GtkWidget *widget, gpointer data){
    db_params *db_params_send = data;

    printf("%d", db_params_send->test);

}

/*int view_product(GtkWidget *widget, gpointer data){
    db_params *db_params_send = data;
    int i = 1;
    int line = 1;
    unsigned int number_champs = 0;
    unsigned long *lengths;

    // Request
    mysql_query(db, "SELECT * FROM PRODUCT");


    // Result recuperation
    res = mysql_use_result(db);

    // Number of elements in one result line
    number_champs = mysql_num_fields(res);

    if(res == NULL){
        printf("There is no result\n");
    }
    else{
        // While there is any result
        while( (row = mysql_fetch_row(res)) ){

            lengths = mysql_fetch_lengths(res);

            printf("%2d - ", line);

            for(i = 1; i <= number_champs; i++){
                printf("%.*s ", (int)lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("euros\n");

            line++;
        }
    }

    return (line - 1);
}*/



void button_action (GtkWidget *widget,MYSQL *db,int tabplat[][2],int id_button)
{
  g_print ("\nAction Bouton\n");
  tabplat[id_button][1]++;
  g_print ("valeur de tab[%d][1] TEST  vaut %d commandes \n",id_button,tabplat[id_button][1]);

  char update[200] = "UPDATE INGREDIENT SET quantity = quantity - 1 WHERE name = 'pork'";
  g_print ("%c",update);
  mysql_query(db,update);
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
