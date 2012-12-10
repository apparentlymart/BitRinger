#ifndef BITCANVAS_H
#define BITCANVAS_H

class BitCanvas {
 public:
    unsigned char * data;
    unsigned int width;
    unsigned int height;
    unsigned int stride;
    unsigned int y_offset;

    BitCanvas(unsigned int width, unsigned int height);
    ~BitCanvas();

    inline void set_pixel(unsigned int x, unsigned int y) {
        this->data[(((y + this->y_offset) % this->height) * this->stride) + (x / 8)] |= 0x1 << (x % 8);
    }
    inline void clear_pixel(unsigned int x, unsigned int y) {
        this->data[(((y + this->y_offset) % this->height) * this->stride) + (x / 8)] &= ~(0x1 << (x % 8));
    }
    inline void write_8_pixels(unsigned int xbyte, unsigned int y, unsigned char pattern) {
        this->data[(((y + this->y_offset) % this->height) * this->stride) + xbyte] = pattern;
    }
    inline void set_8_pixels(unsigned int xbyte, unsigned int y, unsigned char pattern) {
        this->data[(((y + this->y_offset) % this->height) * this->stride) + xbyte] |= pattern;
    }
    inline void clear_8_pixels(unsigned int xbyte, unsigned int y, unsigned char pattern) {
        this->data[(((y + this->y_offset) % this->height) * this->stride) + xbyte] &= ~pattern;
    }
};

#endif
