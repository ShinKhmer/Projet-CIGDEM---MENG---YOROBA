#include <stdio.h>
#include <stdlib.h>
#include "ez-draw.h"
#include "ez-draw_functions.h"
#include "functions.h"

void menu(char *);

int main(int argc, char **argv)
{
    char choice;

	menu(&choice);

	switch(choice){
		case '1' :
		printf("Choisir son menu \n");
		break;
		case '2' :
		printf("Ajouter ingredient \n");

		break;
		case '3' :
		printf("Promotion \n");

		break;
		case '4' :
		printf("Choisir Table et place \n");
		ez_menu();


		break;
		case '5' :
		printf("Finaliser la commande \n");

		break;
		case '0' :
		printf("Quitter \n");

		break;
		default :
		printf("Choix par défaut \n");
    }

    return 0;
}
