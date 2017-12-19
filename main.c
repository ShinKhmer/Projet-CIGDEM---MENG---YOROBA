#include <stdio.h>
#include <stdlib.h>
#include "ez-draw.h"
#include "functions.h"

int main(int argc, char **argv)
{
    if (ez_init() < 0) exit(1);

    ez_window_create (400, 300, "Demo 01: Hello World", NULL);

    ez_main_loop ();
    exit(0);


    return 0;
}
