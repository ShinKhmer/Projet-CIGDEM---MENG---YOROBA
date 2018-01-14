// PROTOTYPES
int search_db_ingredient(MYSQL *, MYSQL_RES *, MYSQL_ROW, char *);
void add_db_ingredient(MYSQL *, char *, char *);
void update_db_ingredient(MYSQL *, char *, char *);

int choose_product(MYSQL *, MYSQL_RES *, MYSQL_ROW , int );
void add_db_product(MYSQL *db, char *, char *);
void link_product_ingredient(MYSQL *, MYSQL_RES *, MYSQL_ROW, char *);

void fgets_correct(char *);


/* Fonction Menu */
// 1. View ingredients
// 2. Add or modify ingredients
// 3. Add menu
// 8. Power on terminals
// 9. Power off terminals
int terminal_print_menu(){
    int choice = 0;

    printf("\n===== TERMINAL MANAGEMENT =====\n\n");
    printf("0. View available ingredients in reserve\n");       // choice 0
    printf("1. Add ingredients in reserve\n");                  // choice 1
    printf("2. Add menu\n");                                    // choice 2
    printf("3. Link ingredients to menu\n");
    printf("8. Power on\n");                                    // choice 8
    printf("9. Power off\n");                                   // choice 9
    printf("\nChoice:\n");
    scanf("%d", &choice);
    system("cls");
    printf("===== RESULT =====\n");

    return choice;
}





/* BDD functions */

void request(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
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


void create_products(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
    char name[50];
    char price[10];
    int i = 0;
    int choice = 0;
    int number = 0;

    fflush(stdin);
    printf("Insert name of the new product :\n");
    fgets(name, 50, stdin);
    fgets_correct(name);

    printf("\nInsert the price of the new product :\n");
    fgets(price, 10, stdin);
    fgets_correct(price);
    printf("\nname: %s - price : %s\n", name, price);

    add_db_product(db, name, price);

    printf("Would you want to link ingredients to this product ?\n");
    while(choice != 1 && choice != 2){
        printf("1. Yes\n2. No\n");
        scanf("%d", &choice);
    }

    if(choice == 1){
        printf("\nLINK STARTO !\n");
        link_product_ingredient(db, res, row, name);
    }
}


int view_product(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
    int i = 1;
    int line = 1;
    int choice_product = 0;
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

    choice_product = choose_product(db, res, row, line-1);

    return choice_product;
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

/*void search_db_product(MYSQL *db, char *name){
    unsigned int i = 1;
    unsigned int number_champs = 0;
    char request[50] = "SELECT * FROM PRODUCT WHERE name='";
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
}*/


void link_product_ingredient(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row, char *name_product){

    // name_product <-> table product
    char ingredient[50];
    int number = 0;
    int i = 0;

    printf("How many ingredients would you want to add ?\n");
    scanf("%d", &number);

    printf("\nnumber: %d\n", number);

    for(i = 0; i < number; i++){
        printf("Insert the ingredient #%d :\n", i);
        fgets(ingredient, 50, stdin);
        fgets_correct(ingredient);
        printf("%s", ingredient);
    }
}




// Correct fgets
void fgets_correct(char *tab){
    int i = 0;
    while(tab[i] != '\n' && tab[i] != '\0')
        i++;

    tab[i] = '\0';
    fflush(stdin);
}

