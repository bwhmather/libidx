/**
 * Checks that `idx_set_int16` can be used to save minus one to a zero
 * dimensional array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t buffer[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x12, 0x34,
    };

    idx_set_int16(buffer, -1, 0);

    idx_assert(buffer[4 + 0] == 0xff);
    idx_assert(buffer[4 + 1] == 0xff);

    return 0;
}

