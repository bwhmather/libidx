/**
 * Tests that all unknown types are recognized as unsupported.
 */
#include "idx.h"

#include "idx_test.h"

#include <limits.h>


int main(void) {
    for (IdxType type = INT_MIN; type < INT_MAX; type++) {
        if (
            type == IDX_TYPE_UINT8 ||
            type == IDX_TYPE_INT8 ||
            type == IDX_TYPE_INT16 ||
            type == IDX_TYPE_INT32 ||
            type == IDX_TYPE_FLOAT ||
            type == IDX_TYPE_DOUBLE
        ) {
            continue;
        }
        idx_assert(!idx_type_supported(type));
    }
    return 0;
}

