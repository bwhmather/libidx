/**
 * Checks that `idx_get_int32` will correctly return a single value from a zero
 * dimensional structure.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0c, 0x00,
        0x77, 0x55, 0x33, 0x11,
    };

    idx_assert(idx_get_int32(data, 0) == 0x77553311);

    return 0;
}
