/**
 * Checks that `idx_init` sets the correct type code when initializing a zero
 * dimensional array of doubles.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    size_t size = idx_size(IDX_TYPE_DOUBLE, 0);

    uint8_t *buffer = calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_DOUBLE, 0);

    const uint8_t expected[] = {
        0x00, 0x00, 0x0e, 0x00,
    };
    idx_assert(memcmp(buffer, expected, 4) == 0);

    return 0;
}

