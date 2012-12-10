
#include <bitcanvas.h>
#include <stdlib.h>

BitCanvas::BitCanvas(unsigned int width, unsigned int height) {
    unsigned int stride = (width + 7) / 8; // round up to the nearest 8
    this->data = (unsigned char *)malloc(stride * height);
    this->stride = stride;
    this->width = width;
    this->height = height;
    this->y_offset = 0;
}

BitCanvas::~BitCanvas() {
    free(this->data);
}
