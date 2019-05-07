/**
 * Checks that `idx_get_int8` will correctly return a single value from a zero
 * dimensional structure.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x09, 0x00,
        0x55,
    };

    idx_assert(idx_get_int8(data, 0) == 0x55);

    return 0;
}
