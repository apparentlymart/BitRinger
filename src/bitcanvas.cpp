
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

void BitCanvas::update_rows(unsigned int start_y, unsigned int end_y) {
    // nothing to do in the base class because we have no
    // display at all.
}

void BitCanvas::update_row(unsigned int y) {
    this->update_rows(y, y);
}

void BitCanvas::update_all() {
    this->update_rows(0, this->height - 1);
}
