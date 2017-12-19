
/* Fonction Menu */
void menu(char *choice){

    int c;
    int d;

	/* Affichage Menu */
	printf("1.Choisir son menu  \n2.Ajouter ingredient	\n3.Promotion	\n4.Choisir Table et place	\n5.Finaliser la commande	\n0. to Quit	\n");

    c = getchar();
    /* Suppresion des caracteres dans stdin */
    if (c != '\n' && c != '\0' ){
        while ( (d = getchar()) != '\n' && d != '\0' );
    }

    *choice = c;
}

