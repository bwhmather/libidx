/**
 * Checks that `idx_get_int32` will abort when passed the wrong number of
 * dimensions.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0c, 0x00,
        0x55, 0x55, 0x55, 0x55,
    };

    idx_assert_aborts(idx_get_int32(data, 1, 0));

    return 0;
}
