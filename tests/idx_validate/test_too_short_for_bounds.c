/**
 * Checks that `idx_validate` correctly rejects structures that have not been
 * allocated enough space to contain their bounds.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x08, 0x02,
        0x00, 0x00, 0x00, 0x03,
        0x00, 0x00, 0x00, 0x03,
        0x01, 0x00, 0x00,
        0x00, 0x01, 0x00,
        0x00, 0x00, 0x01,
    };

    idx_assert(idx_validate(data, 11) == IDX_ERROR_TRUNCATED);

    return 0;
}
