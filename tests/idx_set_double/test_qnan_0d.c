/**
 * Checks that `idx_set_double` will correctly encode quiet NaNs.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const double value = NAN;

    const size_t size = idx_size(IDX_TYPE_DOUBLE, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_DOUBLE, 0);
    idx_set_double(buffer, value, 0);

    // Check sign bit is set to zero.
    idx_assert(!(buffer[4 + 0] & 0x80));

    // Check that the exponent is set to all ones.
    idx_assert((buffer[4 + 0] & 0x7f) == 0x7f);
    idx_assert((buffer[4 + 1] & 0xf0) == 0xf0);

    // Check that only the most significant bit of the significand is set.
    idx_assert((buffer[4 + 1] & 0x0f) == 0x08);
    idx_assert(buffer[4 + 2] == 0x00);
    idx_assert(buffer[4 + 3] == 0x00);
    idx_assert(buffer[4 + 4] == 0x00);
    idx_assert(buffer[4 + 5] == 0x00);
    idx_assert(buffer[4 + 6] == 0x00);
    idx_assert(buffer[4 + 7] == 0x00);

    free(buffer);

    return 0;
}
