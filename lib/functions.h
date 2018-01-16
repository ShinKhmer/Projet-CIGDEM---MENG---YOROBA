// PROTOTYPES
int terminal_print_menu();

void view_ingredient(MYSQL *, MYSQL_RES *, MYSQL_ROW);
int search_db_ingredient(MYSQL *, MYSQL_RES *, MYSQL_ROW, char *);
void add_db_ingredient(MYSQL *, char *, char *);
void update_db_ingredient(MYSQL *, char *, char *);
int recuperation_id_ingredient(MYSQL *, MYSQL_RES *, MYSQL_ROW, char *);

//int view_product(MYSQL *, MYSQL_RES *, MYSQL_ROW);
void create_product(MYSQL *, MYSQL_RES *, MYSQL_ROW );
int choose_product(MYSQL *, MYSQL_RES *, MYSQL_ROW , int );
void add_db_product(MYSQL *db, char *, char *);

void link_product_ingredient(MYSQL *, MYSQL_RES *, MYSQL_ROW, int);
void add_db_link_product_ingredient(MYSQL *, MYSQL_RES *, MYSQL_ROW, int, int);

void fgets_correct(char *);


/* Fonction Menu */
int terminal_print_menu(){
    int choice = 0;

    printf("\n===== TERMINAL MANAGEMENT =====\n\n");
    printf("0. View available ingredients in reserve\n");       // choice 0
    printf("1. Add ingredients in reserve\n");                  // choice 1
    printf("2. View available products\n");                     // choice 2
    printf("3. Add products\n");                                // choice 3
    printf("4. Link ingredients to menu\n");                    // choice 4
    printf("8. Power on\n");                                    // choice 8
    printf("9. Power off\n");                                   // choice 9
    printf("\nChoice:\n");
    scanf("%d", &choice);
    system("cls");
    printf("===== RESULT =====\n");

    return choice;
}




/* INGREDIENTS FUNCTIONS */
//void view_ingredient(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row)
void view_ingredient(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){

    unsigned int i = 1;
    unsigned int number_champs = 0;
    unsigned long *lengths;

    // Request
    mysql_query(db, "SELECT * FROM INGREDIENT");

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

            for(i = 1; i <= number_champs; i++){
                printf("%.*s ", (int)lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }
}

void insert_ingredients(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
    char name[50];
    char number[10];
    int cnt = 0;

    printf("Which ingredient would you want to add ?\n");
    scanf("%s", name);

    fflush(stdin);

    printf("\nHow many would you want to add ?\n");
    scanf("%s", number);

    fflush(stdin);

    cnt = search_db_ingredient(db, res, row, name);

    if(cnt == 0){
        // Add
        add_db_ingredient(db, name, number);
    }else{
         // Update
        update_db_ingredient(db, name, number);
    }
}

int search_db_ingredient(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row, char *name){
    unsigned int i = 1;
    unsigned int number_champs = 0;
    char request[50] = "SELECT * FROM INGREDIENT WHERE name='";
    int cnt = 0;

    strcat(request, name);
    strcat(request, "'");
    // request = "SELECT name FROM INGREDIENT WHERE name='{name}'"

    // Request
    mysql_query(db, request);

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
            for(i = 1; i <= number_champs; i++){
                cnt++;
            }
        }
    }
    return cnt;
}

void add_db_ingredient(MYSQL *db, char *name, char *number){
    char add[200] = "INSERT INTO INGREDIENT VALUES(NULL, '";

    strcat(add, name);
    strcat(add, "', ");
    strcat(add, number);
    strcat(add, ")");
    printf("%s", add);
    mysql_query(db, add);
    printf("\nAdd ingredient: %lu\n", (unsigned long)mysql_affected_rows(db));
}

void update_db_ingredient(MYSQL *db, char *name, char *number){
    char update[200] = "UPDATE INGREDIENT SET quantity=";

    strcat(update, number);
    strcat(update, " WHERE name='");
    strcat(update, name);
    strcat(update, "'");
    mysql_query(db, update);
    printf("\nModify ingredient: %lu\n", (unsigned long)mysql_affected_rows(db));
}

int recuperation_id_ingredient(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row, char *name_ingredient){
    int id_ingredient = 0;
    char request[100] = "SELECT id_ingredient FROM INGREDIENT WHERE name='";

    strcat(request, name_ingredient);
    strcat(request, "'");

    // Request
    mysql_query(db, request);

    // Result recuperation
    res = mysql_use_result(db);

    if(res == NULL){
        printf("There is no result\n");
    }
    else{
        // While there is any result
        while( (row = mysql_fetch_row(res)) ){
            id_ingredient = atoi(row[0]);
        }
    }

    return id_ingredient;
}




/* PRODUCTS FUNCTIONS */

int view_product(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
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
}

void create_product(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
    char name[50];
    char price[10];

    fflush(stdin);
    printf("Insert name of the new product :\n");
    fgets(name, 50, stdin);
    fgets_correct(name);

    printf("\nInsert the price of the new product :\n");
    fgets(price, 10, stdin);
    fgets_correct(price);
    printf("\nname: %s - price : %s\n", name, price);

    add_db_product(db, name, price);
}

int choose_product(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row, int line){
    int choice_product = 0;

    do{
        printf("\nPlease type the number of the product\n");
        scanf("%d", &choice_product);
    }while(choice_product < 1 || choice_product > line);

    return choice_product;
}


void add_db_product(MYSQL *db, char *name, char *price){
    char add[200] = "INSERT INTO PRODUCT VALUES(NULL, '";

    strcat(add, name);
    strcat(add, "', ");
    strcat(add, price);
    strcat(add, ")");
    printf("%s", add);
    mysql_query(db, add);
    printf("\nAdd product: %lu\n", (unsigned long)mysql_affected_rows(db));
}



void link_product_ingredient(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row, int id_product){
    // name_product <-> table product
    char ingredient[50];
    int number = 0;
    int i = 0;
    int check_ingredient = 0;   // if check_ingredient > 0 : ok | if check_ingredient == 0 : not ok
    int id_ingredient = 0;

    printf("\nHow many ingredients would you want to add ?\n");
    scanf("%d", &number);

    printf("\nnumber: %d\n", number);

    fflush(stdin);
    for(i = 0; i < number; i++){
            check_ingredient = 0;
        while(check_ingredient == 0){
            printf("\nType the ingredient #%d (type help for having a look at the ingredients):\n", i);
            fgets(ingredient, 50, stdin);
            fgets_correct(ingredient);
            check_ingredient = search_db_ingredient(db, res, row, ingredient);
            if(check_ingredient > 0){
                id_ingredient = recuperation_id_ingredient(db, res, row, ingredient);
                add_db_link_product_ingredient(db, res, row, id_product, id_ingredient);
            }
            else if(strcmp(ingredient, "help") == 0){
                view_ingredient(db, res, row);
            }
            else{
                printf("\nPlease type an existing ingredient !\n");
            }
        }
    }
}

void add_db_link_product_ingredient(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row, int id_product, int id_ingredient){
    char add[200] = "INSERT INTO LINK_PRODUCT_INGREDIENT VALUES(";
    char string_id_product[5];
    char string_id_ingredient[5];

    sprintf(string_id_product, "%d", id_product);
    sprintf(string_id_ingredient, "%d", id_ingredient);

    strcat(add, string_id_product);
    strcat(add, ", ");
    strcat(add, string_id_ingredient);
    strcat(add, ")");
    mysql_query(db, add);
    printf("\nAdd product: %lu\n", (unsigned long)mysql_affected_rows(db));
}



// Correct fgets
void fgets_correct(char *tab){
    int i = 0;
    while(tab[i] != '\n' && tab[i] != '\0')
        i++;

    tab[i] = '\0';
    fflush(stdin);
}

