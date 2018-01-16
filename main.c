#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <gtk/gtk.h>
#include "lib\functions_gtk.h"
#include "lib\functions.h"


// INIT GTK
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *notebook;
    GtkWidget *vbox2;
    GtkWidget *vbox3;
    GtkWidget *vbox4;
    GtkWidget *vbox5;
    GtkWidget *array;
    GtkWidget *button;
    GtkWidget *pTabLabel;
    GtkWidget *image;
    gchar *sTabLabel;

int main(int argc, char **argv){

    db_params tab_struct[13];
    // Variable
    int i = 0;
    int status;
    int choice = 0;
    int choice_product = 0;
    int line = 0;
    int tab[2] = {NULL};     // struct pt for button
    // tableau a double dimension
    //Stockera l'id du plat et le nombre de commande du plat
    int tabplat[13][2]={{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},
                        {7,0},{8,0},{9,0},{10,0},{11,0},{12,0},{13,0}};







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



        // Init db struc


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




	                            /** INITIALISATION DE GTK **/
	                            gtk_init(&argc, &argv);

	                            /** ETAPE 1 **/
	                            /** CREATION DE LA FENETRE **/
	                            window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	                            createWinGTK(window);

	                            /** ETAPE 2 **/
	                            vbox = gtk_vbox_new(FALSE, 0); /** CREATION DU BOX ORIENTEE VERTICALEMENT (OU HORIZONTALEMENT SELON VOTRE CHOIX) **/
	                            gtk_container_add(GTK_CONTAINER(window), vbox); /** AJOUT DE LA VBOX DANS LA FENETRE **/

	                            /** ETAPE 3 **/
	                            notebook = gtk_notebook_new(); /** CREATION D'UN NOTEBOOK **/
	                            gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0); /** AJOUT DU NOTEBOOK DANS LA VBOX **/
	                            gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP); /** DEFINITION DE LA POSITION DES ONGLETS: top, bottom, left, right POSSIBLES **/

	                            gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), TRUE);

	                            gtk_container_add(GTK_CONTAINER(window), vbox); /** ON AJOUTE LA VBOX A LA FENETRE **/
	                            vbox2 = gtk_vbox_new(FALSE, 0);
	                            gtk_container_add(GTK_CONTAINER(window), vbox2);
	                            /** VOTRE CONTENU ICI **/
	                            array = gtk_table_new(3, 5, TRUE); /** TABLE DE 3 LIGNES 5 COLONNES A VOUS DE CHOISIR **/
	                            gtk_box_pack_start(GTK_BOX(vbox2), array, FALSE, FALSE, 10);

                                /** JOUEZ AVEC LES POSITIONS DES LIGNES ET DES COLONNES POUR LE POSITIONNEMENT DE VOS BOUTONS **/

                                db_params db = { .mysql = database, .result = result, .row = row, .id = 1, .counter = 0 };
                                search_info(&db);
                                db_params db2 = { .mysql = database, .result = result, .row = row, .id = 2, .counter = 0 };
                                search_info(&db2);
                                db_params db3 = { .mysql = database, .result = result, .row = row, .id = 3, .counter = 0 };
                                search_info(&db3);
                                db_params db4 = { .mysql = database, .result = result, .row = row, .id = 4, .counter = 0 };
                                search_info(&db4);
                                db_params db5 = { .mysql = database, .result = result, .row = row, .id = 5, .counter = 0 };
                                search_info(&db5);
                                db_params db6 = { .mysql = database, .result = result, .row = row, .id = 6, .counter = 0 };
                                search_info(&db6);
                                db_params db7 = { .mysql = database, .result = result, .row = row, .id = 7, .counter = 0 };
                                search_info(&db7);
                                db_params db8 = { .mysql = database, .result = result, .row = row, .id = 8, .counter = 0 };
                                search_info(&db8);
                                db_params db9 = { .mysql = database, .result = result, .row = row, .id = 9, .counter = 0 };
                                search_info(&db9);
                                db_params db10 = { .mysql = database, .result = result, .row = row, .id = 10, .counter = 0 };
                                search_info(&db10);
                                db_params db11 = { .mysql = database, .result = result, .row = row, .id = 11, .counter = 0 };
                                search_info(&db11);
                                db_params db12 = { .mysql = database, .result = result, .row = row, .id = 12, .counter = 0 };
                                search_info(&db12);
                                db_params db13 = { .mysql = database, .result = result, .row = row, .id = 13, .counter = 0 };
                                search_info(&db13);
                                total total_db = {db, db2, db3, db4, db5, db6, db7, db8, db9, db10, db11, db12, db13};




	                            button = gtk_button_new_with_label(db.name);
                                image = gtk_image_new_from_file("image/Ramen Pork.jpg");
                                gtk_table_attach(GTK_TABLE(array), button, 0, 1, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
                                gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db);
                                printf("oro");


	                            button = gtk_button_new_with_label(db2.name);
	                            image = gtk_image_new_from_file("image/Ramen Fish.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 1, 2, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db2);


                                button = gtk_button_new_with_label(db3.name);
	                            image = gtk_image_new_from_file("image/Ramen Beef.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 2, 3, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db3);


                                button = gtk_button_new_with_label(db4.name);
	                            image = gtk_image_new_from_file("image/Chicken and Rice.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 3, 4, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db4);


                                button = gtk_button_new_with_label(db5.name);
	                            image = gtk_image_new_from_file("image/Fish and Rice.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 4, 5, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db5);

                                button = gtk_button_new_with_label(db6.name);
	                            image = gtk_image_new_from_file("image/Yakisoba.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 0, 1, 1, 2, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db6);


                                button = gtk_button_new_with_label(db7.name);
	                            image = gtk_image_new_from_file("image/Tempura.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 1, 2, 1, 2, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db7);


                                button = gtk_button_new_with_label(db8.name);
	                            image = gtk_image_new_from_file("image/Oden.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 2, 3, 1, 2, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db8);


                                button = gtk_button_new_with_label(db9.name);
	                            image = gtk_image_new_from_file("image/Omuraisu.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 3, 4, 1, 2, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db9);



                                button = gtk_button_new_with_label(db10.name);
	                            image = gtk_image_new_from_file("image/Sushi.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 4, 5, 1, 2, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db10);


                                button = gtk_button_new_with_label(db11.name);
	                            image = gtk_image_new_from_file("image/Katsudon.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 0, 1, 2, 3, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db11);


                                button = gtk_button_new_with_label(db12.name);
	                            image = gtk_image_new_from_file("image/Onigiri.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 1, 2, 2, 3, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db12);


                                button = gtk_button_new_with_label(db13.name);
	                            image = gtk_image_new_from_file("image/Miso Soup.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 2, 3, 2, 3, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);
                                g_signal_connect(button,"clicked", G_CALLBACK (test),&db12);

                                /*button = gtk_button_new_with_label("Annuler");
                                gtk_table_attach(GTK_TABLE(array), button, 3, 4, 3, 4, !GTK_EXPAND, !GTK_FILL, 0, 0);
                                g_signal_connect(button,"clicked", G_CALLBACK (button_reset),NULL);*/


                                button = gtk_button_new_with_label("Commander");
                                gtk_table_attach(GTK_TABLE(array), button, 4, 5, 3, 4, !GTK_EXPAND, !GTK_FILL, 0, 0);
                                g_signal_connect(button,"clicked", G_CALLBACK (total_price),&total_db);




	                            sTabLabel = g_strdup_printf("Menu"); /** NOM DE VOTRE ONGLET **/
	                            pTabLabel = gtk_label_new(sTabLabel); /** CREATION D'UN LABEL PERMETTANT DE L'INSERER AU NOTEBOOK **/

	                            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox2, pTabLabel); /** INSERTION DE LA PAGE **/

	                            vbox3 = gtk_vbox_new(FALSE, 0);
	                            gtk_container_add(GTK_CONTAINER(window), vbox3);

	                            sTabLabel = g_strdup_printf("Dessert"); /** NOM DE VOTRE ONGLET2 **/
	                            pTabLabel = gtk_label_new(sTabLabel); /** CREATION D'UN LABEL PERMETTANT DE L'INSERER AU NOTEBOOK **/

	                            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox3, pTabLabel); /** INSERTION DE LA PAGE **/

                                button = gtk_button_new_with_label("Mochi");
	                            image = gtk_image_new_from_file("image/mochi.jpg");
	                            gtk_table_attach(GTK_TABLE(array), button, 0, 1, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            gtk_container_add (GTK_CONTAINER (button), image);
                                gtk_button_set_image_position (button,GTK_POS_BOTTOM);
                                gtk_button_set_image (button,image);

	                            vbox4 = gtk_vbox_new(FALSE, 0);
	                            gtk_container_add(GTK_CONTAINER(window), vbox4);

                                sTabLabel = g_strdup_printf("Ingredient"); /** NOM DE VOTRE ONGLET3 **/
	                            pTabLabel = gtk_label_new(sTabLabel); /** CREATION D'UN LABEL PERMETTANT DE L'INSERER AU NOTEBOOK **/
                                gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox4, pTabLabel); /** INSERTION DE LA PAGE **/

                                vbox5 = gtk_vbox_new(FALSE, 0);
	                            gtk_container_add(GTK_CONTAINER(window), vbox5);

                                sTabLabel = g_strdup_printf("Table et Finaliser"); /** NOM DE VOTRE ONGLET3 **/
	                            pTabLabel = gtk_label_new(sTabLabel); /** CREATION D'UN LABEL PERMETTANT DE L'INSERER AU NOTEBOOK **/
                                gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox5, pTabLabel); /** INSERTION DE LA PAGE **/

	                            /** AFFICHAGE DE TOUS LES ELEMENTS DANS LA FENETRE **/
	                            gtk_widget_show_all(window);

	                            gtk_main();
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
