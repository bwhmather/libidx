/**
 * Checks that correct size is given for a structure that hits the limit of
 * what can fit in a `size_t`.
 */
#include "idx.h"

#include "idx_test.h"


int main(int argc, char **argv) {
    // Assumes that `size_t` is 64 bits.
    // Constants are derived from the prime factors of 2^64 - 25.
    // -25 is enough for 1 byte to stay in bounds plus 5 * 4 bytes to store
    // the bounds plus 4 bytes for the magic number.
    size_t size = idx_size(0x08, 5, 4294967291, 3384529, 47, 9, 3);
    idx_assert(size == 0xffffffffffffffff);

    return 0;
}
