#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <gtk/gtk.h>
#include "lib\functions.h"
#include "lib\gtk_functions.h"



int main(int argc, char **argv){

    // INIT GTK
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *notebook;
    GtkWidget *vbox2;
    GtkWidget *vbox3;
    GtkWidget *array;
    GtkWidget *button;

    GtkWidget *pTabLabel;
    gchar *sTabLabel;

    // Variable
    int status;
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

    /* //GTK WINDOW
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    */

    // CONNEXION BDD
    if(mysql_real_connect(database, "localhost", "root", "", "base_restaurant", 0, NULL, 0)){

        // Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row = NULL;
        //request(database, result, row);


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
	                            gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); /** LA FENETRE SERA POSITIONNEEE AU MILIEU **/
	                            gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720); /** DIMENSION DE LA FENETRE **/
	                            gtk_window_set_title(GTK_WINDOW(window), "CIGMENYO"); /** TITRE DE LA FENETRE **/

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

	                            button = gtk_button_new_with_label("Button 1");
	                            gtk_table_attach(GTK_TABLE(array), button, 0, 1, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);
	                            button = gtk_button_new_with_label("Button 2");
	                            gtk_table_attach(GTK_TABLE(array), button, 1, 2, 0, 1, !GTK_EXPAND, !GTK_FILL, 0, 0);

	                                                                    /** JOUEZ AVEC LES POSITIONS DES LIGNES ET DES COLONNES POUR LE POSITIONNEMENT DE VOS BOUTONS **/

	                            sTabLabel = g_strdup_printf("Onglet 1"); /** NOM DE VOTRE ONGLET **/
	                            pTabLabel = gtk_label_new(sTabLabel); /** CREATION D'UN LABEL PERMETTANT DE L'INSERER AU NOTEBOOK **/

	                            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox2, pTabLabel); /** INSERTION DE LA PAGE **/

	                            vbox3 = gtk_vbox_new(FALSE, 0);
	                            gtk_container_add(GTK_CONTAINER(window), vbox3);

	                            sTabLabel = g_strdup_printf("Onglet 2"); /** NOM DE VOTRE ONGLET2 **/
	                            pTabLabel = gtk_label_new(sTabLabel); /** CREATION D'UN LABEL PERMETTANT DE L'INSERER AU NOTEBOOK **/

	                            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox3, pTabLabel); /** INSERTION DE LA PAGE **/


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

    //ez_menu();
    return 0;
}
