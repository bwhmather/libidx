#include "idx.h"

#include "idx_test.h"


int main(void) {
    idx_assert_aborts(idx_bound("\x00\x00\x08\x00\xAB", 1));

    return 0;
}
