
/***************************************

 Random straight lines against the SDL
 backend.

****************************************/

#include <stdio.h>
#include <SDL/SDL.h>
#include <bitcanvas_sdl.h>
#include <stdlib.h>

void draw_a_line(BitCanvas_SDL *c) {
    int x1 = random() % 96;
    int x2 = random() % 96;
    int y1 = random() % 96;
    int y2 = random() % 96;
    c->draw_line(x1, y1, x2, y2);
}

int main(int argc, char **argv) {
    BitCanvas_SDL c(96, 96);

    c.repeat_until_window_closed(draw_a_line, 500);
}
