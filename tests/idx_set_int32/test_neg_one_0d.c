/**
 * Checks that `idx_set_int32` can be used to save minus one to a zero
 * dimensional array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t buffer[] = {
        0x00, 0x00, 0x0c, 0x00,
        0xde, 0xad, 0xbe, 0xef,
    };

    idx_set_int32(buffer, -1, 0);

    idx_assert(buffer[4 + 0] == 0xff);
    idx_assert(buffer[4 + 1] == 0xff);
    idx_assert(buffer[4 + 2] == 0xff);
    idx_assert(buffer[4 + 3] == 0xff);

    return 0;
}

