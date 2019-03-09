/**
 * Checks that a zero dimensional array of doubles has enough space to store
 * exactly one value.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    size_t size = idx_size(IDX_TYPE_DOUBLE, 0);
    idx_assert(size == 12);

    return 0;
}
