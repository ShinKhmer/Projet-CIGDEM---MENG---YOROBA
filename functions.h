
/* Fonction Menu */
char menu(){

	int c;

	/* Affichage Menu */
	printf("1.  \n2.	\n3.	\n4.	\n5.	\n0. to Quit	\n");

		c = getchar();
		/* Suppresion des caracteres dans stdin */
		if (c != '\n' && c != EOF ){
			int d;
			while ( (d = getchar()) != '\n' && d != EOF);
		}
return c;
}
