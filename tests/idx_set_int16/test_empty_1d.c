/**
 * Checks that `idx_set_int16` will correctly abort when called on an empty one
 * dimensional array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x01,
        0x00, 0x00, 0x00, 0x00
    };

    idx_assert_aborts(idx_set_int16(data, 0x1234, 1, 0));

    return 0;
}
