/**
 * Checks that `idx_validate` will correctly reject structures that have not
 * been allocated enough space for all of their data.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x08, 0x01,
        0x00, 0x00, 0x00, 0x03,
        0x01, 0x02, 0x03,
    };

    idx_assert(idx_validate(data, 9) == IDX_ERROR_TRUNCATED);

    return 0;
}
