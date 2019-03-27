/**
 * Checks that `idx_init` will always abort when passed an unrecognized type
 * code.
 */
#include "idx.h"

#include "idx_test.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>


int main(void) {
    // Allocate enough space to fit the biggest possible 3x3 matrix.
    size_t max_size = idx_size(IDX_TYPE_DOUBLE, 2, 3, 3);

    uint8_t *buffer = calloc(max_size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    // Scanning the full range of 32 bit integers is sadly far too slow.  -1024
    // to 1024 gets us outside the range of possible type codes so is probably
    // sufficient, and scanning it takes about as long as the other long tests
    // in the suite.
    for (IdxType type = -1024; type < 1024; type++) {
        if (
            type == IDX_TYPE_UINT8 ||
            type == IDX_TYPE_INT8 ||
            type == IDX_TYPE_INT16 ||
            type == IDX_TYPE_INT32 ||
            type == IDX_TYPE_FLOAT ||
            type == IDX_TYPE_DOUBLE
        ) {
            continue;
        }

        // Check that `idx_init` rejects the request.
        idx_assert_aborts(idx_init(buffer, type, 2, 3, 3));
        
        // Check that `idx_init` didn't write anything to the buffer.
        for (size_t i=0; i < max_size; i++) {
            idx_assert(buffer[i] == 0);
        }
    }
    return 0;
}

