/* Fonction Menu */
// 1. Afficher ingrédients
// 2. Ajouter ingrédients
// 3. Ajouter menu - lié aux ingrédients
// 4.
int terminal_print_menu(){
    int choice = 0;

    printf("\n===== TERMINAL MANAGEMENT =====\n\n");
    printf("0. View available ingredients in reserve\n");       // choice 0
    printf("1. Add ingredients in reserve\n");                  // choice 1
    printf("2. Add menu\n");                                    // choice 2
    printf("8. Power on\n");                                    // choice 8
    printf("9. Power off\n");                                   // choice 9
    printf("\nChoice:\n");
    scanf("%d", &choice);
    system("cls");
    printf("===== RESULT =====\n");

    return choice;
}





/* Fonctions BDD */

void request(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
    unsigned int i = 1;
    unsigned int number_champs = 0;
    unsigned long *lengths;

    //Requête
    mysql_query(db, "SELECT * FROM INGREDIENT;");

    //Récupération des résultats
    res = mysql_use_result(db);

    //Récupération du nombre d'éléments dans une ligne de résultat
    number_champs = mysql_num_fields(res);

    if(res == NULL){
        printf("There is no result\n");
    }
    else{
        //Tant qu'il y a des résultats
        while( (row = mysql_fetch_row(res)) ){

            lengths = mysql_fetch_lengths(res);

            for(i = 1; i <= number_champs; i++){
                printf("%.*s ", (int)lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }
}


void insert_db(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row){
    char name[50];
    char update[200] = "UPDATE INGREDIENT SET quantity=";
    char add[200] = "INSERT INTO INGREDIENT VALUES(NULL, '";
    char number[10];
    int cnt = 0;

    printf("Which ingredient would you want to add ?\n");
    scanf("%s", name);

    fflush(stdin);

    printf("\nHow many would you want to add ?\n");
    scanf("%s", number);

    fflush(stdin);

    cnt = search_db(db, res, row, name);

    printf("\ncnt: %d\n", cnt);

    if(cnt == 0){
        // Add
        strcat(add, name);
        strcat(add, "', ");
        strcat(add, number);
        strcat(add, ")");
        printf("%s", add);
        mysql_query(db, add);
        printf("\nAdd ingredient: %lu\n", (unsigned long)mysql_affected_rows(db));
    }else{
         // Update
        strcat(update, number);
        strcat(update, " WHERE name='");
        strcat(update, name);
        strcat(update, "'");
        mysql_query(db, update);
        printf("\Modify ingredient: %lu\n", (unsigned long)mysql_affected_rows(db));
    }
}


int search_db(MYSQL *db, MYSQL_RES *res, MYSQL_ROW row, char name[50]){
    unsigned int i = 1;
    unsigned int number_champs = 0;
    char request[50] = "SELECT name FROM INGREDIENT WHERE name='";
    int cnt = 0;

    strcat(request, name);
    strcat(request, "'");
    // request = "SELECT name FROM INGREDIENT WHERE name='{name}'"

    //Requête
    mysql_query(db, request);

    //Récupération des résultats
    res = mysql_use_result(db);

    //Récupération du nombre d'éléments dans une ligne de résultat
    number_champs = mysql_num_fields(res);

    if(res == NULL){
        printf("There is no result\n");
    }
    else{
        //Tant qu'il y a des résultats
        while( (row = mysql_fetch_row(res)) ){
            for(i = 1; i <= number_champs; i++){
                cnt++;
            }
        }
    }
    return cnt;
}
