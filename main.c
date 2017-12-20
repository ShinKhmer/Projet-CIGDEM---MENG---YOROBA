#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "ez-draw.h"
#include "ez-draw_functions.h"
#include "functions.h"

// PROTOTYPES

int main(int argc, char **argv){

    MYSQL mysql;

    mysql_init(&mysql);

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");


    if(mysql_real_connect(&mysql, "localhost", "root", "", "base_restaurant", 0, NULL, 0)){

        printf("connected\n");
        mysql_close(&mysql);
        printf("mysql closed");
    }else{
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }




    //ez_menu();
    return 0;
}
