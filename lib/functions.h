
/* Fonction Menu */
// 1. Afficher ingr�dients
// 2. Ajouter ingr�dients
// 3. Ajouter menu - li� aux ingr�dients
// 4.
void terminal_print_menu(int *choice){
    printf("\n===== TERMINAL MANAGEMENT =====\n\n");
    printf("View available ingredients in reserve\n");   // choice 0
    printf("Add ingredients in reserve\n");                // choice 1
    printf("Add menu\n");                                        // choice 2
    printf("\nChoice:\n");
    scanf("%d", choice);
    system("cls");
    printf("===== RESULT =====\n");
}





/* Fonctions BDD */

void request(MYSQL *db, MYSQL *res, MYSQL_ROW row){

    unsigned int i = 1;
    unsigned int number_champs = 0;
    unsigned long *lengths;

    //Requ�te
    mysql_query(db, "SELECT * FROM INGREDIENT;");

    //R�cup�ration des r�sultats
    res = mysql_use_result(db);

    //R�cup�ration du nombre d'�l�ments dans une ligne de r�sultat
    number_champs = mysql_num_fields(res);

    if(res == NULL){
        printf("There is no result\n");
    }
    else{
        //Tant qu'il y a des r�sultats
        while(row = mysql_fetch_row(res)){

            lengths = mysql_fetch_lengths(res);

            for(i = 1; i < number_champs; i++){
                printf("%.*s ", (int)lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }

}

void insert_db(MYSQL *db, MYSQL *res, MYSQL_ROW row){
    unsigned int i = 1;
    unsigned int number_champs = 0;

    mysql_query(db, "UPDATE INGREDIENT SET quantity=20 WHERE name='tomate'");

    check_change_db(db);
}


void check_change_db(MYSQL *db){
    printf("%ld", mysql_affected_rows(db));
}
