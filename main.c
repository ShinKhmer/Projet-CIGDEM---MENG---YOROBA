#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "lib/ez-draw.h"
#include "lib/ez-draw_functions.h"
#include "lib/functions.h"

// PROTOTYPES

int main(int argc, char **argv){

    // INITIALISATION BDD
    MYSQL *database = NULL;
    database = mysql_init(database);

    if(database == NULL){
        printf("\nProblème lors de l'initialisation de la base de données !\n");
        return  0;
    }

    mysql_options(database, MYSQL_READ_DEFAULT_GROUP, "option");


    // CONNEXION BDD
    if(mysql_real_connect(database, "localhost", "root", "", "base_restaurant", 0, NULL, 0)){

        //Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;

        request(database, result, row);

        insert_db(database, result, row);


        mysql_free_result(result);
        mysql_close(database);
    }else{
        printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
    }

    ez_menu();
    return 0;
}
