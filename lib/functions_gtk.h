// PROTOTYPES
void createWinGTK(GtkWidget *window);
void view_product(GtkWidget *widget, gpointer data);


// A VOIR
void apply_button(GtkWidget *button,GtkWidget *image,GtkWidget *array;);
void button_reset (GtkWidget *widget,gpointer data,int **tabplat);
void button_order (GtkWidget *widget,gpointer data,MYSQL *db, MYSQL_RES *res, MYSQL_ROW row);


// STRUCTURES
typedef struct db_params{
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int id;
    char name[30];
    double price;
    int counter;

}db_params;

typedef struct total{
    db_params db;
    db_params db2;
    db_params db3;
    db_params db4;
    db_params db5;
}total;


//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

void test(GtkWidget *window, gpointer data){
    db_params *db_params_send = data;

    db_params_send->counter = 5;
    printf("id = %d, name = %s, price = %.2lf, cnt = %d\n", db_params_send->id, db_params_send->name, db_params_send->price,db_params_send->counter);

    data = db_params_send;
}


void search_info(db_params *db){

    int id_ingredient = 0;
    char number[10];
    char name[30];
    char request[100] = "SELECT name, price FROM PRODUCT WHERE id_product=";


    sprintf(number, "%d", db->id);
    strcat(request, number);

    // Request
    mysql_query(db->mysql, request);

    // Result recuperation
    db->result = mysql_use_result(db->mysql);
    if(db->result == NULL){
        printf("There is no result\n");
    }
    else{
        // While there is any result
        while( (db->row = mysql_fetch_row(db->result)) ){
            strcpy(db->name, (db->row)[0]);
            db->price = atof((db->row)[1]);
        }
    }
}

void total_price(GtkWidget *widget, gpointer data){
    double price = 0;
    total *total_retrieve = data;
    printf("%d", total_retrieve->db.counter);

    if( (total_retrieve->db.counter != 0) ){
        price += total_retrieve->db.counter * total_retrieve->db.price;
    }
    if(total_retrieve->db.counter != 0){
        price += total_retrieve->db2.counter * total_retrieve->db2.price;
    }
    if(total_retrieve->db.counter != 0){
        price += total_retrieve->db3.counter * total_retrieve->db3.price;
    }
    if(total_retrieve->db.counter != 0){
        price += total_retrieve->db4.counter * total_retrieve->db4.price;
    }
    if(total_retrieve->db.counter != 0){
        price += total_retrieve->db5.counter * total_retrieve->db5.price;
    }

    price = total_retrieve->db.price * total_retrieve->db.counter;


    printf("TOTAL : %.2lf", price);
}

/*void init_db_params(int id_button, MYSQL *database, db_params *db){
    db->mysql = database;
    db->result = NULL;
    db->row = NULL;
    db->id = id_button;
}*/

/*void view_product(GtkWidget *widget, gpointer data){
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
        }
    }

}*/


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
