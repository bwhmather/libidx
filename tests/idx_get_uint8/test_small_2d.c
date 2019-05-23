/**
 * Checks that `idx_get_uint8` will return the expected values for all points
 * on and around a small 2d array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x08, 0x02,
        0x00, 0x00, 0x00, 0x03,
        0x00, 0x00, 0x00, 0x04,
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c,
    };

    idx_assert(idx_get_uint8(data, 2, 0, 0) == 0x01);
    idx_assert(idx_get_uint8(data, 2, 1, 0) == 0x05);
    idx_assert(idx_get_uint8(data, 2, 2, 0) == 0x09);
    idx_assert_aborts(idx_get_uint8(data, 2, 3, 0));

    idx_assert(idx_get_uint8(data, 2, 0, 1) == 0x02);
    idx_assert(idx_get_uint8(data, 2, 1, 1) == 0x06);
    idx_assert(idx_get_uint8(data, 2, 2, 1) == 0x0a);
    idx_assert_aborts(idx_get_uint8(data, 2, 3, 1));

    idx_assert(idx_get_uint8(data, 2, 0, 2) == 0x03);
    idx_assert(idx_get_uint8(data, 2, 1, 2) == 0x07);
    idx_assert(idx_get_uint8(data, 2, 2, 2) == 0x0b);
    idx_assert_aborts(idx_get_uint8(data, 2, 3, 2));

    idx_assert(idx_get_uint8(data, 2, 0, 3) == 0x04);
    idx_assert(idx_get_uint8(data, 2, 1, 3) == 0x08);
    idx_assert(idx_get_uint8(data, 2, 2, 3) == 0x0c);
    idx_assert_aborts(idx_get_uint8(data, 2, 3, 3));

    idx_assert_aborts(idx_get_uint8(data, 2, 0, 4));
    idx_assert_aborts(idx_get_uint8(data, 2, 1, 4));
    idx_assert_aborts(idx_get_uint8(data, 2, 2, 4));
    idx_assert_aborts(idx_get_uint8(data, 2, 3, 4));

    return 0;
}
