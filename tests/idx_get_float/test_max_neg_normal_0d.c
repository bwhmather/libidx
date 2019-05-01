/**
 * Tests that `idx_get_float` can read the closest representable non-denormal
 * number to zero.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0d, 0x00,
        0x80, 0x80, 0x00, 0x00,
    };

    const float expected = ldexpf(-1.0, -126);
    idx_assert(idx_get_float(data, 0) == expected);

    return 0;
}

