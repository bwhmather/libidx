/**
 * Checks that `idx_get_uint8` will abort when passed the wrong number of
 * dimensions.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x08, 0x00,
        0x55,
    };

    idx_assert_aborts(idx_get_uint8(data, 1, 0));

    return 0;
}
