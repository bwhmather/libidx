/**
 * Checks that a zero dimensional uint16 array has enough space to store
 * exactly one value.
 */
#include "idx.h"

#include "idx_test.h"


int main(int argc, char **argv) {
    size_t size = idx_size(IDX_TYPE_UINT16, 0);
    idx_assert(size == 6);

    return 0;
}