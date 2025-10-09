#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

int
main(int argc, const char *const argv[])
{
    int ret, k;

    if (argc < 3)
      {
        fprintf(stderr, "Usage: %s <test_name> <k>\n", argv[0]);
        fprintf(stderr, "  test_name: performance, basic, all\n");
        fprintf(stderr, "  k: 1-8 (K value for 2^K-ary tree)\n");
        return -1;
      }

    k = atoi(argv[2]);
    if (k <= 0 || k > 8)
      {
        fprintf(stderr, "Invalid K value: %d (must be 1-8)\n", k);
        return -1;
      }

    if (strcmp(argv[1], "performance") == 0)
      {
        ret = test_performance(k);
        if (ret < 0)
          {
            fprintf(stderr, "Performance test failed\n");
            return -1;
          }
      }
    else if (strcmp(argv[1], "basic") == 0)
      {
        ret = test_basic(k);
        if (ret < 0)
          {
            fprintf(stderr, "Basic test failed\n");
            return -1;
          }
      }
    else if (strcmp(argv[1], "all") == 0)
      {
        ret = test_performance(k);
        if (ret < 0)
          {
            fprintf(stderr, "Performance test failed\n");
            return -1;
          }
        ret = test_basic(k);
        if (ret < 0)
          {
            fprintf(stderr, "Basic test failed\n");
            return -1;
          }
      }
    else
      {
        fprintf(stderr, "Unknown test: %s\n", argv[1]);
        fprintf(stderr, "Available tests: performance, basic, all\n");
        return -1;
      }

    return 0;
}