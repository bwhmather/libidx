/**
 * Checks that libidx can be used to save positive infinity to a zero
 * dimensional double array.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const double value = INFINITY;

    const size_t size = idx_size(IDX_TYPE_DOUBLE, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_DOUBLE, 0);
    idx_set_double(buffer, value, 0);

    // Check sign bit is set to zero.
    idx_assert(!(buffer[4 + 0] & 0x80));

    // Check that biased exponent is set to all ones..
    idx_assert((buffer[4 + 0] & 0x7f) == 0x7f);
    idx_assert((buffer[4 + 1] & 0xf0) == 0xf0);

    // Check that the biased mantissa is set to zero.
    idx_assert((buffer[4 + 1] & 0x0f) == 0x00);
    idx_assert(buffer[4 + 2] == 0x00);
    idx_assert(buffer[4 + 3] == 0x00);
    idx_assert(buffer[4 + 4] == 0x00);
    idx_assert(buffer[4 + 5] == 0x00);
    idx_assert(buffer[4 + 6] == 0x00);
    idx_assert(buffer[4 + 7] == 0x00);

    free(buffer);

    return 0;
}
