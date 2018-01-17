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

    GtkWidget* label;
    gchar* TexteConverti = NULL;


    GtkWidget *view;
    GtkTextBuffer *buffer;

int main(int argc, char **argv){


    // Variable
    int i = 0;
    int j = 0;
    int k = 0;
    int cnt = 0;
    int choice = 0;
    int choice_product = 0;
    int line = 0;
    char string_image[100];
    char string_button[50];
    char string_number[4];
    // tableau a double dimension
    button_datas *start = NULL;
    button_datas *tab[13] = {NULL};
    button_datas *test_struct = NULL;

    test_struct = malloc(sizeof(button_datas));

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




        //Menu
        // 0. View ingredients
        // 1. Add or modify ingredients
        // 2. View products
        // 3. Add products
        // 4. Add existing ingredients to products
        // 8. Power on terminals
        // 9. Power off terminals
        /*while(choice != 9){
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
	                case 8:     // Power on, open terminals with gtk*/


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
        vbox2 = gtk_vbox_new(TRUE, 100);
        gtk_container_add(GTK_CONTAINER(window), vbox2);
        /** VOTRE CONTENU ICI **/
        array = gtk_table_new(3, 5, TRUE); /** TABLE DE 3 LIGNES 5 COLONNES A VOUS DE CHOISIR **/
        gtk_box_pack_start(GTK_BOX(vbox2), array, FALSE, FALSE, 10);

        /** JOUEZ AVEC LES POSITIONS DES LIGNES ET DES COLONNES POUR LE POSITIONNEMENT DE VOS BOUTONS **/


        // Init struct
        cnt = 0;
        for(i = 0; i < 13; i++){
            if(i!=0 && i%5 == 0){
                j = 0;
                k++;
            }

            start = add_button_datas(start, database, i+1);
            tab[i] = start;
            test_struct = tab[i];
            printf("%d", test_struct->id);
            search_info(tab[i]);
            printf("%s\n", test_struct->name);

            strcpy(string_button, tab[i]->name);
            if(tab[i]->counter > 0){
                sprintf(string_number, "%d", tab[i]->counter);
                strcat(string_button, " -> ");
                strcat(string_button, string_number);
            }
            button = gtk_button_new_with_label(string_button);
            sprintf(string_image, "image/%s.jpg\0", tab[i]->name);
            image = gtk_image_new_from_file(string_image);
            gtk_table_attach(GTK_TABLE(array), button, j, j+1, k, k+1, !GTK_EXPAND, !GTK_FILL, 0, 0);
            gtk_container_add (GTK_CONTAINER (button), image);
            gtk_button_set_image_position (button,GTK_POS_BOTTOM);
            gtk_button_set_image (button,image);
            g_signal_connect(button,"clicked", G_CALLBACK (button_pressed),tab[i]);

            /*view = gtk_text_view_new ();
            gtk_container_add (GTK_CONTAINER (button), view);
            buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
            gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);*/



            j++;
        }



        TexteConverti = g_locale_to_utf8("Bonjour\n", -1, NULL, NULL, NULL);
        label = gtk_label_new (TexteConverti);
        g_free(TexteConverti);
        gtk_table_attach(GTK_TABLE(array), button, j, j+1, k, k+1, !GTK_EXPAND, !GTK_FILL, 0, 0);
        gtk_container_add (GTK_CONTAINER (button), label);





        /*button = gtk_button_new_with_label("Cancel");
        gtk_table_attach(GTK_TABLE(array), button, 3, 4, 3, 4, !GTK_EXPAND, !GTK_FILL, 0, 0);
        g_signal_connect(button,"clicked", G_CALLBACK (button_reset),tab);*/


        button = gtk_button_new_with_label("Command");
        gtk_table_attach(GTK_TABLE(array), button, 4, 5, 3, 4, !GTK_EXPAND, !GTK_FILL, 0, 0);
        g_signal_connect(button,"clicked", G_CALLBACK (total_price),tab);


        sTabLabel = g_strdup_printf("Menu"); /** NOM DE VOTRE ONGLET **/
        pTabLabel = gtk_label_new(sTabLabel); /** CREATION D'UN LABEL PERMETTANT DE L'INSERER AU NOTEBOOK **/
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox2, pTabLabel); /** INSERTION DE LA PAGE **/




        /** AFFICHAGE DE TOUS LES ELEMENTS DANS LA FENETRE **/
        gtk_widget_show_all(window);

        gtk_main();
	                            /*break;
	                case 9:     printf("Thank you for using this app !\nPower off the terminal ...");
	                            break;
	                default:    break;
	            }
        }*/
        // Free struct
        while(start != NULL){
            start = delete_button_datas(start);
            mysql_close(database);
        }
        free(test_struct);
    }else{
        printf("Problem while connecting to database !\n");
    }

    return 0;
}
