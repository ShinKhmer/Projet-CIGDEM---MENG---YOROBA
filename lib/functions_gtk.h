// PROTOTYPES
void createWinGTK(GtkWidget *window);



// STRUCTURES
typedef struct button_datas{
    MYSQL *mysql;
    int id;
    char name[30];
    double price;
    int counter;
    struct db_params *next;
}button_datas;





button_datas *add_button_datas(button_datas *start, MYSQL *database, int id_product){
    button_datas *bd;

    bd = malloc(sizeof(button_datas));
    bd->mysql = database;
    bd->id = id_product;
    bd->counter = 0;
    bd->next = start;

    return bd;
}

button_datas *delete_button_datas(button_datas *start){
    button_datas *del = start;
    if(del != NULL){
        start = start->next;
        free(del);
    }
    return start;
}



//Creation fenetre , soucis ici au pasage en fonction
void createWinGTK(GtkWidget *window){
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 720); /** DIMENSION DE LA FENETRE **/
    gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/
}

void button_pressed(GtkWidget *button, gpointer data){
    button_datas *bd = data;

    (bd->counter)++;
    printf("id = %d, name = %s, price = %.2lf, cnt = %d\n", bd->id, bd->name, bd->price, bd->counter);
}


void search_info(button_datas *db){

    int id_ingredient = 0;
    char number[10];
    char name[30];
    char request[100] = "SELECT name, price FROM PRODUCT WHERE id_product=";
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;

    sprintf(number, "%d", db->id);
    strcat(request, number);

    // Request
    mysql_query(db->mysql, request);

    // Result recuperation
    res = mysql_use_result(db->mysql);
    if(res == NULL){
        printf("There is no result\n");
    }
    else{
        // While there is any result
        while( (row = mysql_fetch_row(res)) ){
            strcpy(db->name, (row[0]));
            db->price = atof((row)[1]);
        }
    }
}

void total_price(GtkWidget *button, gpointer data){
    int i = 0;
    int id = 0;
    double price = 0;
    button_datas **address = data;      // Retrieve the tab with all the addresses of all the structs

    // Request orders informations
    id = orders_max_id(address[0]->mysql) + 1;
    printf("INVOICE #%d\n", id);
    for(i = 0; i < 13; i++){
        price += address[i]->counter * address[i]->price;
        if(address[i]->counter > 0)
            printf("\nx%d  %s\n     %.2lf x%d =\t%.2lf",  address[i]->counter, address[i]->name, address[i]->price, address[i]->counter, address[i]->counter * address[i]->price);
    }
    printf("\n===============================\n");
    printf("TOTAL :\t\t%.2lf euros", price);
    insert_orders_datas(address[0]->mysql, price);
    file_print(address, id, price);
}

void file_print(button_datas ** address, int id_invoice, double price){
    char file_name[50];
    char file_content[500];
    char inter[100];
    int i = 0;
    FILE *invoice;

    sprintf(file_name, "invoices/INVOICE %d.txt", id_invoice);
    printf("%s", file_name);
    invoice = fopen(file_name, "wt");

    sprintf(file_content,"===== INVOICE %d =====\n");
    for(i = 0; i < 13; i++){
        if(address[i]->counter > 0){
            sprintf(inter,"\nx%d  %s\n     %.2lf x%d =\t%.2lf",  address[i]->counter, address[i]->name, address[i]->price, address[i]->counter, address[i]->counter * address[i]->price);
            strcat(file_content, inter);
        }
    }
    sprintf(inter, "\n================================\nTOTAL :\t\t%.2lf euros", price);
    strcat(file_content, inter);


    fwrite(file_content, sizeof(char), strlen(file_content), invoice);

    fclose(invoice);
}


int orders_max_id(MYSQL *database){
    int id = 0;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;

    // Request
    mysql_query(database, "SELECT MAX(id_order) FROM ORDERS");

    // Result recuperation
    res = mysql_use_result(database);
    if(res == NULL){
        return 0;
    }
    else{
        // While there is any result
        while( (row = mysql_fetch_row(res)) ){
            return atof((row)[0]);
        }
    }

}

void insert_orders_datas(MYSQL *database, double price){
    char string_db[100];
    char string_price[10] = "\0";

    sprintf(string_price, "%.2lf", price);
    change_comma_to_point(string_price);
    // Request

    sprintf(string_db, "INSERT INTO ORDERS(total_price, id_terminal, id_table) VALUES('%s', 1, 1)", string_price);
    printf("\n%s\n", string_db);
    mysql_query(database, string_db);
    if((unsigned long)mysql_affected_rows(database) > 1){
        printf("Send failed !\n");
    }else{
        printf("Send success !\n");
    }
    printf("Impression en cours du ticket\n");

}

void change_comma_to_point(char *str){
    int i = 0;
    while(str[i] != ',' && i < strlen(str)){
        i++;
    }
    str[i] = '.';
}
