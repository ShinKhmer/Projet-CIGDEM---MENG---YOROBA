#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "ez-draw.h"
#include "ez-draw_functions.h"
#include "functions.h"

// PROTOTYPES

int main(int argc, char **argv){

    MYSQL *database = NULL;
    database = mysql_init(database);

    if(database == NULL){
        printf("\nProblème lors de l'initialisation de la base de données !\n");
        return  0;
    }

    mysql_options(database, MYSQL_READ_DEFAULT_GROUP, "option");

    if(mysql_real_connect(database, "localhost", "root", "", "base_restaurant", 0, NULL, 0)){

        // TEST REQUETES

        request(database);


        mysql_close(database);
    }else{
        printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
    }

    //ez_menu();
    return 0;
}
