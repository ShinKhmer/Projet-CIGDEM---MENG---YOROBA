
/* Fonction Menu */
char menu(){

	int c;

	/* Affichage Menu */
	printf("1.  \n
			2.	\n
			3.	\n
			4.	\n
			5.	\n
			0. to Quit	\n");

		c = getchar();
		/* Suppresion des caracteres dans stdin */
		if (c != '\n' && c != EOF ){
			int d;
			while ( (d = getchar()) != '\n' && d != EOF);
		}

	}
return c;
}
