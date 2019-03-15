/**
 * Checks that `idx_type` will correctly identify a structure containing 16 bit
 * integers..
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = "\x00\x00\x00\x00\xFE";

    for (IdxType type = 0; type < 0xff; type++) {
        data[2] = (uint8_t) type;
        idx_assert(idx_type(data) == type);
    }
    return 0;
}
