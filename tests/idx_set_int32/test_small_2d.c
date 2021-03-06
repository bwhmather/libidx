/**
 * Checks that `idx_set_int32` can be used to set every value in a small 2d
 * array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t buffer[] = {
        0x00, 0x00, 0x0c, 0x02,
        0x00, 0x00, 0x00, 0x04,
        0x00, 0x00, 0x00, 0x03,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
        0xde, 0xad, 0xbe, 0xef,
    };

    idx_set_int32(buffer, 0x01110211, 2, 0, 0);
    idx_set_int32(buffer, 0x07220811, 2, 1, 0);
    idx_set_int32(buffer, 0x0d330e11, 2, 2, 0);
    idx_set_int32(buffer, 0x13441411, 2, 3, 0);
    idx_assert_aborts(idx_set_int32(buffer, 0x00000000, 2, 4, 0));

    idx_set_int32(buffer, 0x03110422, 2, 0, 1);
    idx_set_int32(buffer, 0x09220a22, 2, 1, 1);
    idx_set_int32(buffer, 0x0f331022, 2, 2, 1);
    idx_set_int32(buffer, 0x15441622, 2, 3, 1);
    idx_assert_aborts(idx_set_int32(buffer, 0x00000000, 2, 4, 1));

    idx_set_int32(buffer, 0x05110633, 2, 0, 2);
    idx_set_int32(buffer, 0x0b220c33, 2, 1, 2);
    idx_set_int32(buffer, 0x11331233, 2, 2, 2);
    idx_set_int32(buffer, 0x17441833, 2, 3, 2);
    idx_assert_aborts(idx_set_int32(buffer, 0x00000000, 2, 4, 2));

    idx_assert_aborts(idx_set_int32(buffer, 2, 0, 3));
    idx_assert_aborts(idx_set_int32(buffer, 2, 1, 3));
    idx_assert_aborts(idx_set_int32(buffer, 2, 2, 3));
    idx_assert_aborts(idx_set_int32(buffer, 2, 3, 3));
    idx_assert_aborts(idx_set_int32(buffer, 2, 4, 3));

    const uint8_t expected[] = {
        0x00, 0x00, 0x0c, 0x02,
        0x00, 0x00, 0x00, 0x04,
        0x00, 0x00, 0x00, 0x03,
        0x01, 0x11, 0x02, 0x11, 0x03, 0x11, 0x04, 0x22, 0x05, 0x11, 0x06, 0x33,
        0x07, 0x22, 0x08, 0x11, 0x09, 0x22, 0x0a, 0x22, 0x0b, 0x22, 0x0c, 0x33,
        0x0d, 0x33, 0x0e, 0x11, 0x0f, 0x33, 0x10, 0x22, 0x11, 0x33, 0x12, 0x33,
        0x13, 0x44, 0x14, 0x11, 0x15, 0x44, 0x16, 0x22, 0x17, 0x44, 0x18, 0x33,
    };

    idx_assert(memcmp(buffer, expected, 60) == 0); 

    return 0;
}
