/**
 * Checks that `idx_type` will correctly identify a structure containing 16 bit
 * integers..
 */
#include "idx.h"

#include "idx_test.h"


int main(int argc, char **argv) {
    idx_type_t type_code = idx_type("\x00\x00\x0D\x00\xFE");
    idx_assert(type_code == IDX_TYPE_FLOAT);

    return 0;
}
