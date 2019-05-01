/**
 * Tests that `idx_get_float` can read negative zero.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0d, 0x00,
        0x80, 0x00, 0x00, 0x00,
    };

    const float expected = -0.0;
    idx_assert(idx_get_float(data, 0) == expected);

    return 0;
}

