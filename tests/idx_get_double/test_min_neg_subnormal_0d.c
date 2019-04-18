/**
 * Tests that `idx_get_double` can be used to read the largest possible
 * negative denormal value
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0e, 0x00,
        0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    const double expected = ldexp(ldexp(1.0, -52) - 1.0, -1022);
    idx_assert(idx_get_double(data, 0) == expected);

    return 0;
}

