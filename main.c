#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <gtk/gtk.h>
#include "lib\functions.h"
#include "lib\gtk_functions.h"
// PROTOTYPES
static void activate (GtkApplication* app,gpointer user_data);



int main(int argc, char **argv){
    GtkApplication *app;
    GtkWidget *button;
    GtkWidget *button_box;
    GtkWidget *gtk_places_sidebar_new (void);

    int status;
    int choice = 0;

    //GTK WINDOW
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

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
        //request(database, result, row);


        //Menu
        while(choice != 9){
            choice = terminal_print_menu();      // view menu instructions

            switch(choice){
                case 0:     request(database, result, row);
                            break;
                case 1:     insert_db(database, result, row);
                            break;
                case 2:
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

    //ez_menu();
    return 0;
}
