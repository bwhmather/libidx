/**
 * Checks that the overflow checks work when multiplying bounds.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    // Assumes that `size_t` is 64 bits.
    size_t size = idx_size(
        IDX_TYPE_INT16, 3,
        0x00000529, 0x077362f1, 0x03544ab8
    );
    idx_assert(size == 0);

    return 0;
}
