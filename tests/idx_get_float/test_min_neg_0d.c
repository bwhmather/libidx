/**
 * Tests that `idx_get_float` can be used to read the lowest representable
 * non-infinite value.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0d, 0x00,
        0xff, 0x7f, 0xff, 0xff,
    };

    const float expected = ldexpf(-1.0 - (1.0 - ldexpf(2.0, -24)), 127);
    idx_assert(idx_get_float(data, 0) == expected);

    return 0;
}

