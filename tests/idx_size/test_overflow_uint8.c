/**
 * Checks that the overflow checks work when multiplying bounds.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    // Assumes that `size_t` is 64 bits.
    size_t size = idx_size(
        0x08, 3,
        0x00000529, 0x06a89570, 0x077362f1
    );
    idx_assert(size == 0);

    return 0;
}
