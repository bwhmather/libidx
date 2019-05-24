/**
 * Tests that `idx_get_float` can recognize a quiet NaN in a zero dimensional
 * array.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0d, 0x00,
        0x7f, 0xc0, 0x00, 0x00,
    };

    idx_assert(isnan(idx_get_float(data, 0)));

    return 0;
}

