/**
 * Checks that `idx_validate` will correctly reject structures that have not
 * been allocated enough space to contain even their headers.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x08, 0x00,
        0xFE,
    };

    idx_assert(idx_validate(data, 3) == IDX_ERROR_TRUNCATED);

    return 0;
}
