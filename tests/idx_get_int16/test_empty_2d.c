/**
 * Checks that `idx_get_int16` will correctly abort when called on an empty two
 * dimensional array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x02,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };

    idx_assert_aborts(idx_get_int16(data, 2, 0, 0));

    return 0;
}
