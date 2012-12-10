
/***************************************

 Simple example of the raw pixel writing
 API against the SDL backend.

****************************************/

#include <stdio.h>
#include <SDL/SDL.h>
#include <bitcanvas_sdl.h>

int main(int argc, char **argv) {

    BitCanvas_SDL c(8, 8);

    c.write_8_pixels(0, 0, 0b01111110);
    c.write_8_pixels(0, 1, 0b10000001);
    c.write_8_pixels(0, 2, 0b10100101);
    c.write_8_pixels(0, 3, 0b10000001);
    c.write_8_pixels(0, 4, 0b10100101);
    c.write_8_pixels(0, 5, 0b10011001);
    c.write_8_pixels(0, 6, 0b10000001);
    c.write_8_pixels(0, 7, 0b01111110);

    // The write_*, set_* and clear_* functions just affect the local
    // buffer, so we must flush to the display manually.
    c.update_all();

    c.wait_until_window_closed();
}
