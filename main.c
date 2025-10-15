#include <stdio.h>
#include <stdint.h>

#include "test.h"
#include "radix.h"

static void
usage (const char *prog)
{
  fprintf (stderr,
           "Usage: %s <route_file> [lookup_file] [delete_file]\n"
           "  <route_file>  : prefixes & nexthops input\n"
           "  [lookup_file] : run basic test with lookups; if omitted, run "
           "performance test\n"
           "  [delete_file] : run basic test with deletions additionally\n",
           prog);
}

int
main (int argc, const char *const argv[])
{
  int ret;
  struct rib_tree *t = NULL;

  if (argc != 2 && argc != 3 && argc != 4)
    {
      usage (argv[0]);
      return -1;
    }

  t = test_load_routes (argv[1]);
  if (t == NULL)
    {
      fprintf (stderr, "Failed to load routes from %s\n", argv[1]);
      return -1;
    }

  if (argc == 2)
    {
      fprintf (stdout, "Running performance test...\n");
      ret = test_performance (t);
      if (ret < 0)
        {
          fprintf (stderr, "Performance test failed\n");
          return -1;
        }
    }
  else if (argc == 3)
    {
      fprintf (stdout, "Running basic test with lookup file %s...\n", argv[2]);
      ret = test_basic (t, argv[2]);
      if (ret < 0)
        {
          fprintf (stderr, "Basic test failed with lookup file %s\n", argv[2]);
          return -1;
        }
    }
  else if (argc == 4)
    {
      fprintf (stdout, "Running basic test with delete file %s...\n", argv[3]);
      ret = test_basic_delete (t, argv[2], argv[3]);
      if (ret < 0)
        {
          fprintf (stderr, "Basic test failed with delete file %s\n", argv[3]);
          return -1;
        }
    }

  rib_free (t);
  return 0;
}