/**
 * Tests that `idx_get_double` can recognize a NaN.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0e, 0x00,
        0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    idx_assert(isnan(idx_get_double(data, 0)));

    return 0;
}

