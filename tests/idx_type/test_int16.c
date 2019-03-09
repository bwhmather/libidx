/**
 * Checks that `idx_type` will correctly identify a structure containing 16 bit
 * integers..
 */
#include "idx.h"

#include "idx_test.h"


int main(int argc, char **argv) {
    IdxType type_code = idx_type("\x00\x00\x0B\x00\xFE");
    idx_assert(type_code == IDX_TYPE_INT16);

    return 0;
}
