/**
 * Checks that `idx_set_int16` will abort when passed the wrong number of
 * dimensions.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x55, 0x55,
    };

    idx_assert_aborts(idx_set_int16(data, 44, 1, 0));

    return 0;
}
