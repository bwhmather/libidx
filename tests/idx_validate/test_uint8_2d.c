/**
 * Checks that `idx_validate` will accept a normal 2d uint8 array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    // A 3x3 identity matrix.
    uint8_t data[] = {
        0x00, 0x00, 0x08, 0x02,
        0x00, 0x00, 0x00, 0x03,
        0x00, 0x00, 0x00, 0x03,
        0x01, 0x00, 0x00,
        0x00, 0x01, 0x00,
        0x00, 0x00, 0x01,
    };

    idx_assert(!idx_validate(data, 21));

    return 0;
}
