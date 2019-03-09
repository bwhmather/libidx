#include "idx.h"

#include "idx_test.h"

#include <limits.h>


int main(int argc, char **argv) {
    for (IdxType type = INT_MIN; type < INT_MAX; type++) {
        if (
            (type == IDX_TYPE_UINT8) ||
            (type == IDX_TYPE_INT8) ||
            (type == IDX_TYPE_INT16) ||
            (type == IDX_TYPE_INT32) ||
            (type == IDX_TYPE_FLOAT) ||
            (type == IDX_TYPE_DOUBLE)
        ) {
            continue;
        }

        size_t size = idx_size(type, 0);
        idx_assert(size == 0);
    }
    return 0;
}

