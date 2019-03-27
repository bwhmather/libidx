/**
 * Checks that `idx_type` will correctly identify an int8 structure.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x09, 0x00,
        0xfe,
    };
    idx_assert(idx_type(data) == IDX_TYPE_INT8);

    return 0;
}
