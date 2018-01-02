
/* Fonction Menu */





/* Fonctions BDD */

void request(MYSQL *db){

    unsigned int i = 1;
    unsigned int number_champs = 0;
    unsigned long *lengths;


    //Requ�te
    mysql_query(db, "SELECT * FROM place");
    //D�claration des objets
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    //R�cup�ration des r�sultats
    result = mysql_use_result(db);

    //R�cup�ration du nombre de r�sultats
    number_champs = mysql_num_fields(result);

    if(result == NULL){
        printf("Il n'y a pas de r�sultat dans la table place");
    }
    else{
        //Tant qu'il y a des r�sultats
        while(row = mysql_fetch_row(result)){

            //Stocker tailles des r�sultats dans le pointeur lengths
            lengths = mysql_fetch_lengths(result);

            for(i = 0; i < number_champs; i++){
                printf("[%.*s]", (int)lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }

    mysql_free_result(result);
}
