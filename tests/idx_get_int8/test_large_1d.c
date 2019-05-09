/**
 * Checks that `idx_get_int8` will correctly handles that require multiple
 * bytes to represent.
 */
#include "idx.h"

#include "idx_test.h"


/**
 * Multiplier and increment for LCG random number generator.
 * See http://en.wikipedia.org/wiki/Linear_congruential_generator.
 */
#define A 1664525
#define C 1013904223


int main(void) {
    uint8_t header[] = {
        0x00, 0x00, 0x09, 0x01,
        0x01, 0x55, 0x33, 0x0f,
    };

    uint8_t *data = (uint8_t *) calloc(sizeof(uint8_t), 0x0155330f + 8);
    idx_assert(data != NULL);

    // Copy the header.
    memcpy(data, header, 8);

    // Initialize the array with pseudo random data.
    uint32_t state = 0;
    for (size_t i = 0; i < 0x0155330f; i++) {
        state = A * state + C;
        uint8_t byte = (state >> 24) & 0xff;
        data[i + 8] = byte;
    }

    // Check that `idx_get_int8` returns the expected value for every index in
    // the array.
    state = 0;
    for (size_t i = 0; i < 0x0155330f; i++) {
        state = A * state + C;
        uint8_t byte = (state >> 24) & 0xff;
        int8_t expected = byte & 0x7f;
        if (byte & 0x80) {
            expected -= 128;
        }
        idx_assert(idx_get_int8(data, 1, i) == expected);
    }

    // Check that we have reached the end of the array.
    idx_assert_aborts(idx_get_int8(data, 1, 0x0155330f));

    free(data);

    return 0;
}