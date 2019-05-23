/**
 * Checks that `idx_set_int16` can be used to save a valid integer to a zero
 * dimensional array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t buffer[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x00, 0x00,
    };

    idx_set_int16(buffer, 0x1234, 0);

    idx_assert(buffer[4 + 0] == 0x12);
    idx_assert(buffer[4 + 1] == 0x34);

    return 0;
}

