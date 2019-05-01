/**
 * Checks that libidx can be used to save the lowest value that can not be
 * represented by a single precision floating point number in normal form.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const float value = ldexpf(ldexpf(1.0, -23) - 1.0, -126);

    const size_t size = idx_size(IDX_TYPE_FLOAT, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_FLOAT, 0);
    idx_set_float(buffer, value, 0);

    // Check sign bit is set to one.
    idx_assert(buffer[4 + 0] & 0x80);

    // Check that biased exponent is set to zero..
    idx_assert((buffer[4 + 0] & 0x7f) == 0x00);
    idx_assert((buffer[4 + 1] & 0x80) == 0x00);

    // Check that the biased mantissa is set to all ones.
    idx_assert((buffer[4 + 1] & 0x7f) == 0x7f);
    idx_assert(buffer[4 + 2] == 0xff);
    idx_assert(buffer[4 + 3] == 0xff);

    free(buffer);

    return 0;
}

