/**
 * Checks that `idx_get_uint8` will correctly handle arrays with bounds that
 * require multiple bytes to represent.
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
        0x00, 0x00, 0x08, 0x02,
        0x00, 0x00, 0x55, 0x33,
        0x00, 0x00, 0x33, 0x0f,
    };

    uint8_t *data = (uint8_t *) calloc(
        sizeof(uint8_t), 0x5533 * 0x330f + 8
    );
    idx_assert(data != NULL);

    // Copy the header.
    memcpy(data, header, 12);

    // Initialize the array with pseudo random data.
    uint32_t state = 0;
    for (size_t i = 0; i < 0x5533 * 0x330f; i++) {
        state = A * state + C;
        data[i + 12] = (state >> 24) & 0xff;
    }

    // Check that `idx_get_uint8` returns the expected value for every index in
    // the array.
    state = 0;
    for (size_t u = 0; u < 0x5533; u++) {
        for (size_t v = 0; v < 0x330f; v++) {
            state = A * state + C;
            uint8_t expected = (state >> 24) & 0xff;

            idx_assert(idx_get_uint8(data, 2, u, v) == expected);
        }
        idx_assert_aborts(idx_get_uint8(data, 2, u, 0x330f));
    }

    for (size_t v = 0; v <= 0x330f; v++) {
        idx_assert_aborts(idx_get_uint8(data, 2, 0x5533, v));
    }

    return 0;
}
