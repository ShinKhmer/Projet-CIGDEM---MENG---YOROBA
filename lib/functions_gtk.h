// PROTOTYPES
void createWinGTK(GtkWidget *window);



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
    db_params db6;
    db_params db7;
    db_params db8;
    db_params db9;
    db_params db10;
    db_params db11;
    db_params db12;
    db_params db13;
}total;


//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

void test(GtkWidget *button, gpointer data){
    db_params *db_params_send = data;

    db_params_send->counter++;
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
    printf("%d %s", total_retrieve->db.counter, total_retrieve->db.name);
    total_retrieve->db.counter++;

    if( (total_retrieve->db.counter != 0) ){
        price += total_retrieve->db.counter * total_retrieve->db.price;
    }
    if(total_retrieve->db2.counter != 0){
        price += total_retrieve->db2.counter * total_retrieve->db2.price;
    }
    if(total_retrieve->db3.counter != 0){
        price += total_retrieve->db3.counter * total_retrieve->db3.price;
    }
    if(total_retrieve->db4.counter != 0){
        price += total_retrieve->db4.counter * total_retrieve->db4.price;
    }
    if(total_retrieve->db5.counter != 0){
        price += total_retrieve->db5.counter * total_retrieve->db5.price;
    }
    if( (total_retrieve->db6.counter != 0) ){
        price += total_retrieve->db6.counter * total_retrieve->db6.price;
    }
    if(total_retrieve->db7.counter != 0){
        price += total_retrieve->db7.counter * total_retrieve->db7.price;
    }
    if(total_retrieve->db8.counter != 0){
        price += total_retrieve->db8.counter * total_retrieve->db8.price;
    }
    if(total_retrieve->db9.counter != 0){
        price += total_retrieve->db9.counter * total_retrieve->db9.price;
    }
    if(total_retrieve->db10.counter != 0){
        price += total_retrieve->db10.counter * total_retrieve->db10.price;
    }
    if( (total_retrieve->db11.counter != 0) ){
        price += total_retrieve->db11.counter * total_retrieve->db11.price;
    }
    if(total_retrieve->db12.counter != 0){
        price += total_retrieve->db12.counter * total_retrieve->db12.price;
    }
    if(total_retrieve->db13.counter != 0){
        price += total_retrieve->db13.counter * total_retrieve->db13.price;
    }





    printf("TOTAL : %.2lf", price);
}
