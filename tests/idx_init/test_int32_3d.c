/**
 * Checks that `idx_init` can correctly create a header for a three dimensional
 * array of thirty two bit integers.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    size_t size = idx_size(IDX_TYPE_INT32, 3, 0x0f, 0x03, 0x01ab);

    uint8_t *buffer = calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_INT32, 3, 0x0f, 0x03, 0x01ab);

    const uint8_t expected[] = {
        0x00, 0x00, 0x0c, 0x03,
        0x00, 0x00, 0x00, 0x0f,
        0x00, 0x00, 0x00, 0x03,
        0x00, 0x00, 0x01, 0xab,
    };
    idx_assert(memcmp(buffer, expected, 16) == 0);

    free(buffer);

    return 0;
}


