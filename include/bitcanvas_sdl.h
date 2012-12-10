#ifndef BITCANVAS_SDL_H
#define BITCANVAS_SDL_H

#include <SDL/SDL.h>
#include <bitcanvas.h>

class BitCanvas_SDL;

typedef void (*BitCanvas_SDL_TimerCallback)(BitCanvas_SDL *c);

class BitCanvas_SDL : public BitCanvas {
 public:
    SDL_Surface *window;

    BitCanvas_SDL(unsigned int width, unsigned int height);
    ~BitCanvas_SDL();

    virtual void update_rows(unsigned int start_y, unsigned int end_y);

    // SDL-specific functions to just wait until our window is closed.
    // These are handy for testing and making static demos.
    void wait_until_window_closed();
    void repeat_until_window_closed(BitCanvas_SDL_TimerCallback cb, Uint32 interval_ms);
};

#endif
