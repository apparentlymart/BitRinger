#ifndef BITCANVAS_SDL_H
#define BITCANVAS_SDL_H

#include <SDL/SDL.h>
#include <bitcanvas.h>

class BitCanvas_SDL : public BitCanvas {
 public:
    SDL_Surface *window;

    BitCanvas_SDL(unsigned int width, unsigned int height);
    ~BitCanvas_SDL();

    virtual void update_rows(unsigned int start_y, unsigned int end_y);

    // SDL-specific function to just wait until our window is closed.
    // this is a handy utility for writing little static demos.
    void wait_until_window_closed();
};

#endif
