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

    bool get_pixel(unsigned int x, unsigned int y);
    void set_pixel(unsigned int x, unsigned int y);
    void clear_pixel(unsigned int x, unsigned int y);
    void write_8_pixels(unsigned int xbyte, unsigned int y, unsigned char pattern);
    void set_8_pixels(unsigned int xbyte, unsigned int y, unsigned char pattern);
    void clear_8_pixels(unsigned int xbyte, unsigned int y, unsigned char pattern);

    virtual void update_rows(unsigned int start_y, unsigned int end_y);
    void update_row(unsigned int y);
    void update_all();

    void draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

 private:
    inline unsigned int swap(unsigned int &a, unsigned int &b) {
        a = a ^ b;
        b = b ^ a;
        a = a ^ b;
    }

};

#endif
