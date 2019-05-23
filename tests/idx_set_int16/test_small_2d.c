/**
 * Checks that `idx_set_int16` can be used to set every value in a small 2d
 * array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t buffer[] = {
        0x00, 0x00, 0x0b, 0x02,
        0x00, 0x00, 0x00, 0x04,
        0x00, 0x00, 0x00, 0x03,
        0xde, 0xad, 0xbe, 0xef, 0xde, 0xad,
        0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef, 0xde, 0xad,
        0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef,
    };

    idx_set_int16(buffer, 0x1111, 2, 0, 0);
    idx_set_int16(buffer, 0x2211, 2, 1, 0);
    idx_set_int16(buffer, 0x3311, 2, 2, 0);
    idx_set_int16(buffer, 0x4411, 2, 3, 0);
    idx_assert_aborts(idx_set_int16(buffer, 0x0000, 2, 4, 0));

    idx_set_int16(buffer, 0x1122, 2, 0, 1);
    idx_set_int16(buffer, 0x2222, 2, 1, 1);
    idx_set_int16(buffer, 0x3322, 2, 2, 1);
    idx_set_int16(buffer, 0x4422, 2, 3, 1);
    idx_assert_aborts(idx_set_int16(buffer, 0x0000, 2, 4, 1));

    idx_set_int16(buffer, 0x1133, 2, 0, 2);
    idx_set_int16(buffer, 0x2233, 2, 1, 2);
    idx_set_int16(buffer, 0x3333, 2, 2, 2);
    idx_set_int16(buffer, 0x4433, 2, 3, 2);
    idx_assert_aborts(idx_set_int16(buffer, 0x0000, 2, 4, 2));

    idx_assert_aborts(idx_set_int16(buffer, 2, 0, 3));
    idx_assert_aborts(idx_set_int16(buffer, 2, 1, 3));
    idx_assert_aborts(idx_set_int16(buffer, 2, 2, 3));
    idx_assert_aborts(idx_set_int16(buffer, 2, 3, 3));
    idx_assert_aborts(idx_set_int16(buffer, 2, 4, 3));

    const uint8_t expected[] = {
        0x00, 0x00, 0x0b, 0x02,
        0x00, 0x00, 0x00, 0x04,
        0x00, 0x00, 0x00, 0x03,
        0x11, 0x11, 0x11, 0x22, 0x11, 0x33,
        0x22, 0x11, 0x22, 0x22, 0x22, 0x33,
        0x33, 0x11, 0x33, 0x22, 0x33, 0x33,
        0x44, 0x11, 0x44, 0x22, 0x44, 0x33,
    };

    idx_assert(memcmp(buffer, expected, 36) == 0); 

    return 0;
}
