/**
 * Checks that the overflow checks work when multiplying bounds.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    // Assumes that `size_t` is 64 bits.
    size_t size = idx_size(0x08, 3, 0xffffffff, 0xffffffff, 0x02);
    idx_assert(size == 0);

    return 0;
}
