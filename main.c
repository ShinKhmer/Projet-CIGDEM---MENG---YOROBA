#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <gtk/gtk.h>
#include "lib\functions.h"
// PROTOTYPES

int main(int argc, char **argv){

    int choice = 0;
    int choice_product = 0;
    int line = 0;

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
        MYSQL_ROW row = NULL;

        //Menu
        // 0. View ingredients
        // 1. Add or modify ingredients
        // 2. View products
        // 3. Add products
        // 4. Add existing ingredients to products
        // 8. Power on terminals
        // 9. Power off terminals
        while(choice != 9){
            choice = terminal_print_menu();      // view menu instructions

            switch(choice){
                case 0:     view_ingredient(database, result, row);
                            break;
                case 1:     insert_ingredients(database, result, row);
                            break;
                case 2:     view_product(database, result, row);
                            break;
                case 3:     create_product(database, result, row);
                            break;
                case 4:     line = view_product(database, result, row);
                            choice_product = choose_product(database, result, row, line);
                            link_product_ingredient(database, result, row, choice_product);
                            break;
                case 8:     // Power on, open terminals with gtk
                            break;
                case 9:     printf("Thank you for using this app !\nPower off the terminal ...");
                            break;
                default:    break;
            }
            mysql_free_result(result);
        }
        mysql_close(database);
    }else{
        printf("Problem while connecting to database !\n");
    }

    return 0;
}
