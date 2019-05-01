/**
 * Checks that libidx can be used to save the lowest possible non-denormalized
 * single precision floating point number.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const float value = ldexpf(1.0, -126);

    const size_t size = idx_size(IDX_TYPE_FLOAT, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_FLOAT, 0);
    idx_set_float(buffer, value, 0);

    // Check sign bit is set to zero.
    idx_assert(!(buffer[4 + 0] & 0x80));

    // Check that biased exponent is set to 127.
    idx_assert((buffer[4 + 0] & 0x7f) == 0x00);
    idx_assert((buffer[4 + 1] & 0x80) == 0x80);

    // Check that the biased mantissa is set to zero.
    idx_assert((buffer[4 + 1] & 0x7f) == 0x00);
    idx_assert(buffer[4 + 2] == 0x00);
    idx_assert(buffer[4 + 3] == 0x00);

    free(buffer);

    return 0;
}
