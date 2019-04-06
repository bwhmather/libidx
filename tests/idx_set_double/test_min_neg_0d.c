/**
 * Checks that libidx can be used to save the lowest possible double precision
 * floating point number.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const double value = ldexp(-1.0 - (1.0 - ldexp(2.0, -53)), 1023);

    const size_t size = idx_size(IDX_TYPE_DOUBLE, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_DOUBLE, 0);
    idx_set_double(buffer, value, 0);

    // Check sign bit is set to zero.
    idx_assert(buffer[4 + 0] & 0x80);

    // Check that biased exponent is set to 1023..
    idx_assert((buffer[4 + 0] & 0x7f) == 0x7f);
    idx_assert((buffer[4 + 1] & 0xf0) == 0xe0);

    // Check that the biased mantissa is set to zero.
    idx_assert((buffer[4 + 1] & 0x0f) == 0x0f);
    idx_assert(buffer[4 + 2] == 0xff);
    idx_assert(buffer[4 + 3] == 0xff);
    idx_assert(buffer[4 + 4] == 0xff);
    idx_assert(buffer[4 + 5] == 0xff);
    idx_assert(buffer[4 + 6] == 0xff);
    idx_assert(buffer[4 + 7] == 0xff);

    free(buffer);

    return 0;
}

