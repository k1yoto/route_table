#include <stdio.h>
#include <string.h>

#include "test.h"

int
main(int argc, const char *const argv[])
{
    int ret;

    if (argc < 2)
      {
        fprintf(stderr, "Usage: %s <test_name>\n", argv[0]);
        fprintf(stderr, "  test_name: performance, basic, all\n");
        return -1;
      }

    if (strcmp(argv[1], "performance") == 0)
      {
        ret = test_performance();
        if (ret < 0) 
          {
            fprintf(stderr, "Performance test failed\n");
            return -1;
          }
      }
    else if (strcmp(argv[1], "basic") == 0)
      {
        ret = test_basic();
        if (ret < 0)
          {
            fprintf(stderr, "Basic test failed\n");
            return -1;
          }
      }
    else if (strcmp(argv[1], "all") == 0)
      {
        ret = test_performance();
        if (ret < 0) 
          {
            fprintf(stderr, "Performance test failed\n");
            return -1;
          }
        ret = test_basic();
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