
#include <bitcanvas.h>
#include <stdlib.h>
#include <string.h>

BitCanvas::BitCanvas(unsigned int width, unsigned int height) {
    unsigned int stride = (width + 7) / 8; // round up to the nearest 8
    this->data = (unsigned char *)malloc(stride * height);
    memset(this->data, 0, stride * height);
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

void BitCanvas::draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
    bool is_steep = abs(y2 - y1) > abs(x2 - x1);

    // normalize so we can always progress along x from low to high
    if (is_steep) {
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);

    int error = dx / 2;
    int ystep = y1 < y2 ? 1 : -1;

    unsigned int x;
    unsigned int y = y1;

    for (x = x1; x <= x2; x++) {
        if (is_steep) {
            // we flipped x/y earlier so now we need to flip back
            this->set_pixel(y, x);
        }
        else {
            this->set_pixel(x, y);
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }

    // Update the affected rows
    if (is_steep) {
        // we flipped x/y earlier so now we need to flip back
        this->update_rows(x1, x2);
    }
    else {
        if (ystep > -1) {
            this->update_rows(y1, y2);
        }
        else {
            this->update_rows(y2, y1);
        }
    }
}
