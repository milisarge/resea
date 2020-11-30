#include <resea/printf.h>
#include <string.h>
#include "test.h"

void libcommon_test(void) {
    TEST_ASSERT(!resea_memcmp("a", "a", 1));
    TEST_ASSERT(!resea_memcmp("a", "b", 0));
    TEST_ASSERT(resea_memcmp("ab", "aa", 2) != 0);

    TEST_ASSERT(!resea_strncmp("a", "a", 1));
    TEST_ASSERT(!resea_strncmp("a", "b", 0));
}
