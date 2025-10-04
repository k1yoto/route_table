#include <stdio.h>

#include "test.h"

int
main(int argc, const char *const argv[])
{
    int ret;

    ret = test_performance();
    if (ret < 0) {
        fprintf(stderr, "Performance test failed\n");
        return -1;
    }

    return 0;
}