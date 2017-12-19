void ez_menu(){

    if (ez_init() < 0) exit(1);

    ez_window_create (400, 300, "Demo 01: Hello World", NULL);

    ez_main_loop ();
}
