/**
 * Checks that `idx_get_int8` will correctly handles that require multiple
 * bytes to represent.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t header[] = {
        0x00, 0x00, 0x0c, 0x01,
        0x01, 0x0f, 0x33, 0x55,
    };

    uint8_t *data = (uint8_t *) calloc(sizeof(uint8_t), 4 * 0x010f3355 + 8);
    idx_assert(data != NULL);

    // Copy the header.
    memcpy(data, header, 8);

    // Initialize the array with pseudo random data.
    uint32_t state = 0;
    for (size_t i = 0; i < 0x010f3355; i++) {
        uint8_t b0 = idx_rnd(&state);
        uint8_t b1 = idx_rnd(&state);
        uint8_t b2 = idx_rnd(&state);
        uint8_t b3 = idx_rnd(&state);

        data[4 * i + 8] = b0;
        data[4 * i + 9] = b1;
        data[4 * i + 10] = b2;
        data[4 * i + 11] = b3;
    }

    // Check that `idx_get_int32` returns the expected value for every index in
    // the array.
    state = 0;
    for (size_t i = 0; i < 0x010f3355; i++) {
        uint8_t b0 = idx_rnd(&state);
        uint8_t b1 = idx_rnd(&state);
        uint8_t b2 = idx_rnd(&state);
        uint8_t b3 = idx_rnd(&state);

        int32_t expected = (
            (((int32_t) b0 & 0x7f) << 24) |
            (((int32_t) b1 & 0xff) << 16) |
            (((int32_t) b2 & 0xff) << 8) |
            (((int32_t) b3 & 0xff) << 0)
        );
        if (b0 & 0x80) {
            expected -= 0x80000000;
        }

        idx_assert(idx_get_int32(data, 1, i) == expected);
    }

    // Check that we have reached the end of the array.
    idx_assert_aborts(idx_get_int32(data, 1, 0x010f3355));

    free(data);

    return 0;
}
