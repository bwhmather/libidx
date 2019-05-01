/**
 * Tests that `idx_get_float` can read negative infinity.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0d, 0x00,
        0xff, 0x80, 0x00, 0x00,
    };

    const float expected = -INFINITY;
    idx_assert(idx_get_float(data, 0) == expected);

    return 0;
}

