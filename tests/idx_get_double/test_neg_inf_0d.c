/**
 * Tests that `idx_get_double` can read negative infinity.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0e, 0x00,
        0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    const double expected = -INFINITY;
    idx_assert(idx_get_double(data, 0) == expected);

    return 0;
}

