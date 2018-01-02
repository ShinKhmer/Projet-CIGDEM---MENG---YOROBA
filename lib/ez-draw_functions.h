// EZ-DRAW TEAM FUNCTIONS
#define SIZE_x 800
#define SIZE_y 600

void ez_menu();
void win1_on_event (Ez_event *ev);
void win2_on_event (Ez_event *ev);
void win1_on_expose (Ez_event *ev);
void win2_on_expose (Ez_event *ev);
void win1_on_key_press (Ez_event *ev);

// on compte les interfaces pour changer d'interface a chaque fois ?
int compteur_interface = 0;

void ez_menu(){
    Ez_window win1;
    Ez_window win2;
    if (ez_init() < 0) exit(1);
    // fenetre client
    ez_window_create (SIZE_x, SIZE_y, "Borne de commande - Client", win1_on_event);
    //fenetre service
    ez_window_create (SIZE_x, SIZE_y, "Borne de gestion - service", win2_on_event);
    printf ("win1 = %d\n", ez_window_get_id(win1));
    printf ("win2 = %d\n", ez_window_get_id(win2));
    ez_main_loop ();
}


void win1_on_event (Ez_event *ev)                /* Called by ez_main_loop() */
{                                                /* for each event on win1   */
    switch (ev->type) {
        case Expose   : win1_on_expose(ev);
                        break;
        case KeyPress : win1_on_key_press(ev);
                        break;
        case ButtonPress :
                        compteur_interface++;
                        ez_window_clear(ev);
                        break;
    }
}

void win2_on_event (Ez_event *ev)                /* Called by ez_main_loop() */
{                                                /* for each event on win1   */
    switch (ev->type) {
        case Expose   : win2_on_expose(ev);
                        break;
        case KeyPress : win1_on_key_press(ev);
                        break;
    }
}

void win1_on_expose (Ez_event *ev)
{
    compteur_interface++;
    int i, w, h;

    ez_window_get_size (ev->win, &w, &h);       // obtain width, height

    ez_set_color (ez_black);
    ez_set_nfont (3);
    if(compteur_interface == 1 ){
    ez_draw_text (ev->win, EZ_TC, w/2, h/2-60,"Bonjour bienvenue chez");        // print
    ez_draw_text (ev->win, EZ_TC, w/2, h/2-30,"CIGMENYO");
    ez_draw_text (ev->win, EZ_TC, w/2, h/2,"Borne de commande client #1");
    ez_draw_text (ev->win, EZ_TC, w/2, h/2+30,"Veuillez taper une fois sur l'écran pour continuer");
    }else if(compteur_interface == 2){
    // ici je vais desssiner des rectangles mais en vrai
    // faut faire appel à ez_image.c et ez_image.h pour mettre des images de plats
    // et un nom de plats en dessous
    ez_draw_text      (ev->win, EZ_BL, 10, 180, "Plat 1");
    ez_draw_rectangle (ev->win, 160, 190, 220, 230);

    }
}

void win2_on_expose (Ez_event *ev)
{
    int i, w, h;

    ez_window_get_size (ev->win, &w, &h);       // obtain width, height

    ez_set_color (ez_black);
    ez_set_nfont (3);
    ez_draw_text (ev->win, EZ_TC, w/2, h/2,"Controle service #1");
    ez_draw_text (ev->win, EZ_TC, w/2, h/2+30,"Veuillez taper une fois sur l'écran pour continuer");
    ez_draw_text (ev->win, EZ_TC, w/2, h/2+60,"q : pour quitter ");
}


void win1_on_key_press (Ez_event *ev)
{
    switch (ev->key_sym) {
        case XK_q : ez_quit(); break;
        case XK_o : compteur_interface++; ez_window_clear(ev); break;
        case XK_n : ez_quit(); break;
    }
}




