#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char **argv)
{
    char menu;
	menu = menu();

	switch(menu){
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

		break;
		case '5' :
		printf("Finaliser la commande \n");

		break;
		case '0' :
		printf("Quitter \n");

		break;
		default :
		printf("Choix par d�faut \n");

    return 0;
}
