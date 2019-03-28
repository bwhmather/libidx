/**
 * Checks that `idx_init` can construct a valid header for three dimensional
 * array of single precision floating point numbers.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    size_t size = idx_size(IDX_TYPE_FLOAT, 3, 0x0400, 0x04, 0x1000);

    uint8_t *buffer = calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_FLOAT, 3, 0x0400, 0x04, 0x1000);
    
    const uint8_t expected[] = {
        0x00, 0x00, 0x0d, 0x03,
        0x00, 0x00, 0x04, 0x00,
        0x00, 0x00, 0x00, 0x04,
        0x00, 0x00, 0x10, 0x00,
    };
    idx_assert(memcmp(buffer, expected, 16) == 0);

    free(buffer);

    return 0;
}

