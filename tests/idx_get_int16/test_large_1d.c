/**
 * Checks that `idx_get_int8` will correctly handles that require multiple
 * bytes to represent.
 */
#include "idx.h"

#include "idx_test.h"


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
        uint8_t msb = idx_rnd(&state);
        uint8_t lsb = idx_rnd(&state);

        data[2 * i + 8] = msb;
        data[2 * i + 9] = lsb;
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
