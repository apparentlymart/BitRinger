
#include <bitcanvas.h>
#include <stdio.h>

int failures = 0;
int successes = 0;

void print_fail_header(const char * desc, const char * function, const char * file, int line) {
    fprintf(
        stderr,
        "\n---------------------------\n"
        "Assertion failed: %s\n"
        "In %s at %s line %i\n"
        "---------------------------\n",
        desc, function, file, line
    );
}

void print_fail_footer() {
    fprintf(
        stderr,
        "---------------------------\n"
    );
}

void _assert_equals(const char * desc, int got, int expected, const char * function, const char * file, int line) {
    if (got == expected) {
        successes++;
    }
    else {
        failures++;
        print_fail_header(desc, function, file, line);
        fprintf(stderr, "Got %i but was expecting %i.\n", got, expected);
        print_fail_footer();
    }
}
#define assert_equals(desc, got, expected) _assert_equals(desc, got, expected, __func__, __FILE__, __LINE__);

void _assert_data_matches(const char * desc, BitCanvas *c, const char * expected, const char * function, const char * file, int line) {
    unsigned int len = c->stride * c->height;
    unsigned char * data = c->data;
    unsigned int wrongs = 0;
    for (int bi = 0; bi < len; bi++) {
        unsigned char pattern = data[bi];
        for (int bit = 0; bit < 8; bit++) {
            bool set = (pattern & (1 << bit)) > 0;
            bool expected_set = expected[bi * 8 + bit] != ' ';
            if (set != expected_set) wrongs++;
        }
    }

    if (wrongs > 0) {
        print_fail_header(desc, function, file, line);
        fprintf(stderr, "Got:\n");
        for (int y = 0; y < c->height; y++) {
            fprintf(stderr, "    |");
            for (int xbyte = 0; xbyte < c->stride; xbyte++) {
                unsigned char pattern = data[y * c->stride + xbyte];
                for (int bit = 0; bit < 8; bit++) {
                    if ((pattern & (1 << bit)) > 0) {
                        fprintf(stderr, "#");
                    }
                    else {
                        fprintf(stderr, " ");
                    }
                }
            }
            fprintf(stderr, "|\n");
        }
        fprintf(stderr, "Expected:\n");
        for (int y = 0; y < c->height; y++) {
            fprintf(stderr, "    |");
            for (int x = 0; x < (c->stride * 8); x++) {
                if (expected[(y * c->stride * 8) + x] != ' ') {
                    fprintf(stderr, "#");
                }
                else {
                    fprintf(stderr, " ");
                }
            }
            fprintf(stderr, "|\n");
        }
        print_fail_footer();
        failures++;
    }
    else {
        successes++;
    }
}
#define assert_data_matches(desc, c, expected) _assert_data_matches(desc, c, expected, __func__, __FILE__, __LINE__);

void test_pixel_ops() {
    BitCanvas c(16, 2);

    c.set_pixel(0, 0);
    assert_data_matches(
        "Top-left pixel is now set",
        &c,
        "#               "
        "                "
    );

    c.set_pixel(1, 0);
    assert_data_matches(
        "Top-left two pixels are now set",
        &c,
        "##              "
        "                "
    );

    c.set_pixel(0, 1);
    assert_data_matches(
        "Three pixels set around the top left corner",
        &c,
        "##              "
        "#               "
    );

    c.set_pixel(9, 0);
    assert_data_matches(
        "9, 0 now set",
        &c,
        "##       #      "
        "#               "
    );

    c.write_8_pixels(0, 0, 0b01010101);
    c.write_8_pixels(1, 0, 0b01010101);
    assert_data_matches(
        "Checkerboard in the top row",
        &c,
        "# # # # # # # # "
        "#               "
    );

    c.set_8_pixels(0, 1, 0b10101010);
    c.set_8_pixels(1, 1, 0b10101010);
    assert_data_matches(
        "Checkerboard in the bottom row except for the leftover pixel at bottom left",
        &c,
        "# # # # # # # # "
        "## # # # # # # #"
    );

    c.clear_pixel(0, 1);
    assert_data_matches(
        "Perfect checkerboard",
        &c,
        "# # # # # # # # "
        " # # # # # # # #"
    );

    c.clear_8_pixels(0, 0, 0b11110000);
    c.clear_8_pixels(1, 1, 0b11110000);
    assert_data_matches(
        "Two chunks of the checkerboard cleared",
        &c,
        "# #     # # # # "
        " # # # # # #    "
    );

    assert_equals("(0, 0) is set", c.get_pixel(0, 0), 1);
    assert_equals("(1, 0) is clear", c.get_pixel(1, 0), 0);
    assert_equals("(2, 0) is set", c.get_pixel(2, 0), 1);
    assert_equals("(0, 1) is clear", c.get_pixel(0, 1), 0);

}

void test_line() {
    {
        // 45 degree lines
        BitCanvas c(8, 8);

        c.draw_line(0, 0, 7, 7);
        assert_data_matches(
            "One diagonal line",
            &c,
            "#       "
            " #      "
            "  #     "
            "   #    "
            "    #   "
            "     #  "
            "      # "
            "       #"
        );

        c.draw_line(7, 0, 0, 7);
        assert_data_matches(
             "A cross",
             &c,
             "#      #"
             " #    # "
             "  #  #  "
             "   ##   "
             "   ##   "
             "  #  #  "
             " #    # "
             "#      #"
        );
    }

    {
        // 90 degree lines
        BitCanvas c(8, 8);

        c.draw_line(0, 2, 0, 5);
        c.draw_line(7, 2, 7, 5);
        c.draw_line(2, 0, 5, 0);
        c.draw_line(2, 7, 5, 7);

        assert_data_matches(
             "A box with the corners missing",
             &c,
             "  ####  "
             "        "
             "#      #"
             "#      #"
             "#      #"
             "#      #"
             "        "
             "  ####  "
        );
    }

    // Various awkward lines
    {
        BitCanvas c(8, 8);

        c.draw_line(0, 0, 7, 3);
        assert_data_matches(
             "A line with two pixels on each row",
             &c,
             "##      "
             "  ##    "
             "    ##  "
             "      ##"
             "        "
             "        "
             "        "
             "        "
        );
    }
    {
        BitCanvas c(8, 8);

        c.draw_line(6, 6, 4, 0);
        assert_data_matches(
             "A tall, skinny line",
             &c,
             "    #   "
             "    #   "
             "     #  "
             "     #  "
             "     #  "
             "      # "
             "      # "
             "        "
        );
    }
}

#define run_tests(func) fprintf(stderr, "*** %s \n", #func); func();

int main() {
    fprintf(stderr, "\n");
    run_tests(test_pixel_ops);
    run_tests(test_line);

    int total = successes + failures;
    fprintf(stderr, "\nRan %i tests (%i failures)\n\n", total, failures);

    return failures > 0 ? 1 : 0;
}
