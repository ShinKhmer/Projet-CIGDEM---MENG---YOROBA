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
        while(row = mysql_fetch_row(res)){

            lengths = mysql_fetch_lengths(res);

            for(i = 1; i < number_champs; i++){
                printf("%.*s ", (int)lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }

}

void insert_db(MYSQL *db){

    mysql_query(db, "UPDATE INGREDIENT SET quantity=12 WHERE name='tomate'");

    printf("\nAdd ingredients: %lu", (unsigned long)mysql_affected_rows(db));

}
