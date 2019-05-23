/**
 * Checks that `idx_set_int32` can be used to save a valid integer to a zero
 * dimensional array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t buffer[] = {
        0x00, 0x00, 0x0c, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };

    idx_set_int32(buffer, 0xdeadbeef, 0);

    idx_assert(buffer[4 + 0] == 0xde);
    idx_assert(buffer[4 + 1] == 0xad);
    idx_assert(buffer[4 + 2] == 0xbe);
    idx_assert(buffer[4 + 3] == 0xef);

    return 0;
}

