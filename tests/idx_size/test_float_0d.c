/**
 * Checks that a zero dimensional array of floats has enough space to store
 * exactly one value.
 */
#include "idx.h"

#include "idx_test.h"


int main(int argc, char **argv) {
    size_t size = idx_size(IDX_TYPE_FLOAT, 0);
    idx_assert(size == 8);

    return 0;
}
