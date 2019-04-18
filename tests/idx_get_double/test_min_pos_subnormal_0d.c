/**
 * Tests that `idx_get_double` can be used to read the smallest possible
 * positive floating point number.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0e, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    };

    const double expected = ldexp(1.0, -1074);
    idx_assert(idx_get_double(data, 0) == expected);

    return 0;
}

