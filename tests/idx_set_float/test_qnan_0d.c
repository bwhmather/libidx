/**
 * Checks that `idx_set_float` will correctly encode quiet NaNs.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const float value = NAN;

    const size_t size = idx_size(IDX_TYPE_FLOAT, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_FLOAT, 0);
    idx_set_float(buffer, value, 0);

    // Check sign bit is set.
    idx_assert(!(buffer[4 + 0] & 0x80));

    // Check that biased exponent is set to zero..
    idx_assert((buffer[4 + 0] & 0x7f) == 0x7f);
    idx_assert((buffer[4 + 1] & 0x80) == 0x80);

    // Check that the biased mantissa is set to zero.
    idx_assert((buffer[4 + 1] & 0x7f) == 0x40);
    idx_assert(buffer[4 + 2] == 0x00);
    idx_assert(buffer[4 + 3] == 0x00);

    free(buffer);

    return 0;
}
