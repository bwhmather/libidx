/**
 * Checks that `idx_get_int32` will correctly abort when called on an empty one
 * dimensional array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0c, 0x01,
        0x00, 0x00, 0x00, 0x00
    };

    idx_assert_aborts(idx_get_int32(data, 1, 0));

    return 0;
}
