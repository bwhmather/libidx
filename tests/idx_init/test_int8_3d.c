/**
 * Checks that `idx_init` sets the correct type code when initializing a zero
 * dimensional array of signed chars.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    size_t size = idx_size(IDX_TYPE_INT8, 3, 0x03, 0x0001ff00, 0x33);

    uint8_t *buffer = calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_INT8, 3, 0x03, 0x0001ff00, 0x33);
    
    const uint8_t expected[] = {
        0x00, 0x00, 0x09, 0x03,
        0x00, 0x00, 0x00, 0x03,
        0x00, 0x01, 0xff, 0x00,
        0x00, 0x00, 0x00, 0x33,
    };
    idx_assert(memcmp(buffer, expected, 16) == 0);

    return 0;
}


