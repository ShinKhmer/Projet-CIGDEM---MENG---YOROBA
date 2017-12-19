
/* Fonction Menu */
void menu(char *choice){

    int c;
    int d;

	/* Affichage Menu */
	printf("1.  \n2.	\n3.	\n4.	\n5.	\n0. to Quit	\n");

    c = getchar();
    /* Suppresion des caracteres dans stdin */
    if (c != '\n' && c != '\0' ){
        while ( (d = getchar()) != '\n' && d != '\0' );
    }

    *choice = c;
}

