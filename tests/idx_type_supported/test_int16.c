/**
 * Checks that `idx_type_supported` returns `true` for IDX_TYPE_INT16.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    idx_assert(idx_type_supported(IDX_TYPE_INT16));

    return 0;
}
