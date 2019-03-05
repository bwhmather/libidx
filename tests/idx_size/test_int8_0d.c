/**
 * Checks that a zero dimensional int8 array has enough space to store exactly
 * one value.
 */
#include "idx.h"

#include "idx_test.h"


int main(int argc, char **argv) {
    size_t size = idx_size(IDX_TYPE_INT8, 0);
    idx_assert(size == 5);

    return 0;
}
