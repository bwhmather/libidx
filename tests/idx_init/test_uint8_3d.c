/**
 * Checks that `idx_init` can correctly construct a header for a three
 * dimensional array of unsigned chars.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    size_t size = idx_size(IDX_TYPE_UINT8, 3, 0x00015533, 3, 5);

    uint8_t *buffer = calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_UINT8, 3, 0x0015533, 3, 5);

    const uint8_t expected[] = {
        0x00, 0x00, 0x08, 0x03,
        0x00, 0x01, 0x55, 0x33,
        0x00, 0x00, 0x00, 0x03,
        0x00, 0x00, 0x00, 0x05,
    };
    idx_assert(memcmp(buffer, expected, 16) == 0);

    free(buffer);

    return 0;
}


