/**
 * Checks that a zero dimensional int32 array has enough space to store exactly
 * one value.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    size_t size = idx_size(IDX_TYPE_INT32, 0);
    idx_assert(size == 8);

    return 0;
}
