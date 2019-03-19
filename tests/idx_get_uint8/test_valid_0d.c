/**
 * Checks that `idx_get_uint8` will correctly return a single value from a zero
 * dimensional structure.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x08, 0x00,
        0x55,
    };

    idx_assert(idx_get_uint8(data, 0) == 0x55);

    return 0;
}
