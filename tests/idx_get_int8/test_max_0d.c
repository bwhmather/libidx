/**
 * Checks that `idx_get_int8` can correctly decode the highest representable
 * number.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x09, 0x00,
        0x7f,
    };

    idx_assert(idx_get_int8(data, 0) == 127);

    return 0;
}

