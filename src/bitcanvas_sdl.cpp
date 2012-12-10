
#include <SDL/SDL.h>
#include <bitcanvas_sdl.h>

BitCanvas_SDL::BitCanvas_SDL(unsigned int width, unsigned int height) : BitCanvas(width, height) {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    this->window = SDL_SetVideoMode(width * 10, height * 10, 0, SDL_SWSURFACE);
    this->update_all();
}

BitCanvas_SDL::~BitCanvas_SDL() {
    SDL_FreeSurface(this->window);
}

void BitCanvas_SDL::update_rows(unsigned int start_y, unsigned int end_y) {
    Uint32 set_color = SDL_MapRGB(this->window->format, 255, 0, 0);
    Uint32 clear_color = SDL_MapRGB(this->window->format, 0, 0, 0);
    SDL_Rect rect;
    rect.w = 10;
    rect.h = 10;
    for (unsigned int y = start_y; y <= end_y; y++) {
        for (unsigned int x = 0; x < this->width; x++) {
            bool set = this->get_pixel(x, y);
            Uint32 color = set ? set_color : clear_color;
            rect.x = x * 10;
            rect.y = y * 10;
            SDL_FillRect(this->window, &rect, color);
        }
    }
    SDL_Flip(this->window);
}

void BitCanvas_SDL::wait_until_window_closed() {
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }
}

Uint32 BitCanvas_SDL_timer_callback(Uint32 interval, void *param) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    SDL_PushEvent(&event);
    return interval;
}

void BitCanvas_SDL::repeat_until_window_closed(BitCanvas_SDL_TimerCallback cb, Uint32 interval_ms) {

    SDL_TimerID timer = SDL_AddTimer(interval_ms, &BitCanvas_SDL_timer_callback, NULL);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_RemoveTimer(timer);
            break;
        }
        else if (event.type == SDL_USEREVENT) {
            cb(this);
        }
    }
}

