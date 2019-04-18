/**
 * Tests that `idx_get_double` can be used to read the largest representable
 * non-infinite value.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0e, 0x00,
        0x7f, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    };

    const double expected = ldexp(1.0 + (1.0 - ldexp(2.0, -53)), 1023);
    idx_assert(idx_get_double(data, 0) == expected);

    return 0;
}

