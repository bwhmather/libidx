/**
 * Checks that `idx_get_int16` can correctly decode positive one.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x00, 0x01,
    };

    idx_assert(idx_get_int16(data, 0) == 1);

    return 0;
}

