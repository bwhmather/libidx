/**
 * Checks that `idx_set_int32` aborts when called on a structure that reports a
 * different type.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x00, 0x00,
        0xde, 0xad, 0xbe, 0xef,
    };

    for (uint8_t type = 0; type < 0xff; type++) {
        if (type == IDX_TYPE_INT32) {
            continue;
        }

        data[2] = type;

        idx_assert_aborts(idx_set_int32(data, 0, 0));
    }

    return 0;
}


