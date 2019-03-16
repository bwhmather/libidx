/**
 * Checks that `idx_init` sets the correct type code when initializing a zero
 * dimensional array of signed 32 bit integers.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    size_t size = idx_size(IDX_TYPE_INT32, 0);
    uint8_t *buffer = calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_INT32, 0);
    
    idx_assert(memcmp(buffer, "\x00\x00\x0C\x00", 4) == 0);

    return 0;
}


