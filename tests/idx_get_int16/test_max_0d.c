/**
 * Checks that `idx_get_int16` can correctly decode the highest representable
 * number.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x7f, 0xff,
    };

    idx_assert(idx_get_int16(data, 0) == 32767);

    return 0;
}

