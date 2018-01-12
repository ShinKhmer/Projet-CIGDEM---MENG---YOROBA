#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <gtk/gtk.h>
#include "lib\functions.h"
// PROTOTYPES

int main(int argc, char **argv){

    int choice = 0;

    // INITIALISATION BDD
    MYSQL *database = NULL;
    database = mysql_init(database);

    if(database == NULL){
        printf("\nProblem while initializing database !\n");
        return  0;
    }

    mysql_options(database, MYSQL_READ_DEFAULT_GROUP, "option");


    // CONNEXION BDD
    if(mysql_real_connect(database, "localhost", "root", "", "base_restaurant", 0, NULL, 0)){

        // Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row = 0;


        //Menu
        while(choice != 9){
            terminal_print_menu(&choice);      // view menu instructions
            switch(choice){
                case 0:     //request(database, result, row);
                            break;
                case 1:
                            break;
                case 2:     insert_db(database, result, row);
                            break;
                case 9:     printf("Thank you for using this app !\nPower off the terminal ...");
                            break;
                default:    break;
            }
        }





        mysql_free_result(result);
        mysql_close(database);
    }else{
        printf("Problem while connecting to database !\n");
    }

    //ez_menu();
    return 0;
}
