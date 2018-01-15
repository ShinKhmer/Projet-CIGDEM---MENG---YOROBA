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
    char name[50];
    int id_terminal = 0 ;

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
        // 2. Add menu
        // 8. Power on terminals
        // 9. Power off terminals
        while(choice != 9){
            choice = terminal_print_menu();      // view menu instructions

            switch(choice){
                case 0:     request(database, result, row);
                            break;
                case 1:     insert_ingredients(database, result, row);
                            break;
                case 2:     create_products(database, result, row);
                            break;
                case 3:     choice_product = view_product(database, result, row);
                            printf("\nchoice_product: %d", choice_product);
                            //link_product_ingredient(database, result, row, name);
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
// CREATION DE LA FACTURE

// Récuparation de l'id terminal

    sprintf(request,"SELECT id_terminal FROM terminal WHERE id_terminal='%d'",id_terminal);
        mysql_query(mysql,request);
        // Result recuperation
        res = mysql_use_result(mysql);
        row = mysql_fetch_row(result);
        mysql_free_result(result);



// Récupération numéro de commande

    sprintf(request,"SELECT id_order FROM order WHERE id_terminal='%d'",id_terminal);
        mysql_query(mysql,request);
        // Result recuperation
        res = mysql_use_result(mysql);
        row = mysql_fetch_row(result);
        mysql_free_result(result);

// Récupération total de la commande

     sprintf(request,"SELECT id_order FROM order WHERE total_price='%d'",total_price);
            mysql_query(mysql,request);
            // Result recuperation
            res = mysql_use_result(mysql);
            row = mysql_fetch_row(result);
            mysql_free_result(result);






    FILE *fact = fopen("facture.txt","a+");
    int word = 0;

    if(fact == NULL) {
        EXIT_SUCCESS

    }
    while ((word = fgetc(fact)) != EOF ) {

            printf ("%c",word)

    }




    fclose(fact)


    //ez_menu();
    return 0;
}
