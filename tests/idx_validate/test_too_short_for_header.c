#include "idx.h"

#include "idx_test.h"


int main(void) {
    IdxError err = idx_validate("\x00\x00\x08\x00\xFE", 3);
    idx_assert(err ==  IDX_ERROR_TRUNCATED);

    return 0;
}
