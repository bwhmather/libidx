/**
 * Checks that `idx_get_int32` can correctly decode zero.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0c, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };

    idx_assert(idx_get_int32(data, 0) == 0);

    return 0;
}

