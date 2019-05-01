/**
 * Tests that `idx_get_float` can be used to read the smallest possible
 * positive floating point number.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0d, 0x00,
        0x00, 0x00, 0x00, 0x01,
    };

    const float expected = ldexpf(ldexpf(1.0, -126), -23);
    idx_assert(idx_get_float(data, 0) == expected);

    return 0;
}

