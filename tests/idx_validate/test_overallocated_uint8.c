/**
 * Checks that `idx_validate` will reject arrays that have been allocated too
 * much space.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x08, 0x02,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x01,
        0x01, 0x00, 0x00,
        0x00, 0x01, 0x00,
        0x00, 0x00, 0x01,
        0xbb,
    };

    idx_assert(idx_validate(data, 22) == IDX_ERROR_OVERALLOCATED);

    return 0;
}
