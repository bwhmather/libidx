/**
 * Checks that `idx_type` will correctly identify an int8 structure.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    IdxType type_code = idx_type("\x00\x00\x09\x00\xFE");
    idx_assert(type_code == IDX_TYPE_INT8);

    return 0;
}
