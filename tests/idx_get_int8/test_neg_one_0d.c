/**
 * Checks that `idx_get_int8` can correctly decode negative one.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x09, 0x00,
        0xff,
    };

    idx_assert(idx_get_int8(data, 0) == -1);

    return 0;
}

