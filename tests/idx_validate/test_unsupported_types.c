/**
 * Checks that `idx_validate` will reject arrays when it does not recognize the
 * type.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x00, 0x00,
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    };

    for (uint8_t type = 0; type < 0xff; type++) {
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

        data[2] = type;

        idx_assert(idx_validate(data, 12) == IDX_ERROR_UNKNOWN_TYPE_CODE);
    }

    return 0;
}


