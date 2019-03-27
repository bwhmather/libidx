/**
 * Checks that `idx_type` will handle all possible type codes, both supported
 * and unsupported..
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x00, 0x00,
    };

    for (IdxType type = 0; type < 0xff; type++) {
        data[2] = (uint8_t) type;
        idx_assert(idx_type(data) == type);
    }
    return 0;
}
