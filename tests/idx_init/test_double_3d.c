/**
 * Checks that `idx_init` can construct a header for a three dimensional array
 * of double precision floating point numbers.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    size_t size = idx_size(IDX_TYPE_DOUBLE, 3, 0xff, 0x03, 0xa033);

    uint8_t *buffer = calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_DOUBLE, 3, 0xff, 0x03, 0xa033);

    const uint8_t expected[] = {
        0x00, 0x00, 0x0e, 0x03,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0x03,
        0x00, 0x00, 0xa0, 0x33,
    };
    idx_assert(memcmp(buffer, expected, 16) == 0);

    return 0;
}

