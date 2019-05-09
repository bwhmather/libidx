/**
 * Checks that `idx_get_int8` will correctly handles that require multiple
 * bytes to represent.
 */
#include "idx.h"

#include "idx_test.h"

/**
 * LCG random number generator.
 * See http://en.wikipedia.org/wiki/Linear_congruential_generator.
 */
static uint8_t idx_rnd(uint32_t *state) {
    const uint32_t A = 1664525;
    const uint32_t C = 1013904223;

    *state = A * (*state) + C;
    return (uint8_t) (((*state) >> 24) & 0xff);
}


int main(void) {
    uint8_t header[] = {
        0x00, 0x00, 0x0b, 0x01,
        0x01, 0x55, 0x33, 0x0f,
    };

    uint8_t *data = (uint8_t *) calloc(sizeof(uint8_t), 2 * 0x0155330f + 8);
    idx_assert(data != NULL);

    // Copy the header.
    memcpy(data, header, 8);

    // Initialize the array with pseudo random data.
    uint32_t state = 0;
    for (size_t i = 0; i < 0x0155330f; i++) {
        data[2 * i + 8] = idx_rnd(&state);
        data[2 * i + 9] = idx_rnd(&state);
    }

    // Check that `idx_get_int8` returns the expected value for every index in
    // the array.
    state = 0;
    for (size_t i = 0; i < 0x0155330f; i++) {
        uint8_t msb = idx_rnd(&state);
        uint8_t lsb = idx_rnd(&state);

        int16_t expected = (
            (((int16_t) msb & 0x7f) << 8) |
            (((int16_t) lsb & 0xff) << 0)
        );
        if (msb & 0x80) {
            expected -= 32768;
        }

        idx_assert(idx_get_int16(data, 1, i) == expected);
    }

    // Check that we have reached the end of the array.
    idx_assert_aborts(idx_get_int16(data, 1, 0x0155330f));

    free(data);

    return 0;
}
