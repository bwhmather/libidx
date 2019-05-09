/**
 * Checks that `idx_get_int16` will correctly return a single value from a zero
 * dimensional structure.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x55, 0x33,
    };

    idx_assert(idx_get_int16(data, 0) == 0x5533);

    return 0;
}
