/**
 * Checks that a zero dimensional uint8 array has enough space to store exactly
 * one value.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    size_t size = idx_size(IDX_TYPE_UINT8, 0);
    idx_assert(size == 5);

    return 0;
}
