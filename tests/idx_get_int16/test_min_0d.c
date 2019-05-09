/**
 * Checks that `idx_get_int16` can correctly decode the lowest representable
 * number.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x80, 0x00,
    };

    idx_assert(idx_get_int16(data, 0) == -32768);

    return 0;
}

