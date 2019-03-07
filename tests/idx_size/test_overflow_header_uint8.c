/**
 * Tests that a structure that contains exceeds the size that can be described
 * by a `size_t` by less than the size of its header will not cause `idx_size`
 * to overflow.
 */
#include "idx.h"

#include "idx_test.h"


int main(int argc, char **argv) {
    // Assumes that `size_t` is 64 bits.
    // Constants are the prime factors of 2^64 - 26.  With a header for 6
    // dimensions, this is 22 bytes too large to be described by a `size_t`.
    // The header will be 28 bytes in length.
    size_t size = idx_size(0x08, 6, 2, 5, 191, 421, 90679, 252986611);
    idx_assert(size == 0);

    return 0;
}
