#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include "radix.h"

/*
 * Xorshift
 * see: https://github.com/drpnd/radix-tree/blob/master/tests/basic.c
 */
static __inline__ uint32_t
xor128(void)
{
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;

    t = x ^ (x<<11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w>>19)) ^ (t ^ (t >> 8));
}

/*
 * see: https://www.cc.u-tokyo.ac.jp/public/VOL8/No5/data_no2_0609.pdf
 */
static double
gettime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int
test_performance (void)
{
  struct rib_tree *t = NULL;
  FILE *fp;
  char line[4096], cider[64], nexthop[64];
  int ret, plen, count = 0;
  uint8_t addr1[4];
  uint64_t res, i;
  uint32_t addr2, rand_addr;
  double tv1, tv2;
  struct in_addr tmp;

  fp = fopen ("tests/rib.20251001.0000.ipv4.txt", "r");
  if (fp == NULL)
      return -1;

  t = rib_new (t);
  if (t == NULL)
      return -1;

  /* Load the routes */
  while (fgets(line, sizeof(line), fp) != NULL)
    {
      ret = sscanf (line, "%63s %63s", cider, nexthop);
      if (ret < 0)
        return -1;

      plen = inet_net_pton(AF_INET, cider, addr1, sizeof(addr1));
      if (plen < 0)
        return -1;

      ret = inet_pton (AF_INET, nexthop, &tmp);
      if (ret < 0)
        return -1;
      addr2 = ntohl(tmp.s_addr);

      ret = rib_route_add (t, addr1, plen, (void *)(uintptr_t)addr2);
      if (ret < 0)
        return -1;

      count++;
    }

  printf ("Total %d routes added\n", count);
  fclose (fp);

  /* Lookup performance test */
  tv1 = gettime ();

  unsigned long long N = 0x10000000ULL;
  res = 0;
  for ( i = 0; i < N; i++ ) {
      rand_addr = xor128();
      res ^= (uint64_t)rib_route_lookup (t, (uint8_t *)&rand_addr);
  }

  tv2 = gettime ();

  /* Print the results */
  printf ("Elapsed time: %.6f sec for %llu lookups\n", tv2 - tv1, N);
  printf ("Lookup per second: %.6fM lookups/sec\n", N / (tv2 - tv1) / 1000000);

  /* Additional test */
  printf ("------------------------------------------------\n");
  printf ("Additional test: lookup\n");
  char buf[64];
  struct rib_node *n;
  uint32_t found_nexthop;
  struct in_addr addr;
  char *key[] = {
      "1.0.0.1",
      "1.0.4.1",
      "1.0.5.1",
      "1.0.6.1",
  };
  int j, k = sizeof(key) / sizeof(key[0]);

  for (j = 0; j < k; j++)
    {
      ret = inet_pton (AF_INET, key[j], &addr);
      if (ret < 0)
          return -1;
      n = rib_route_lookup (t, (uint8_t *)&addr);
      if (n)
        {
          found_nexthop = (uint32_t)(uintptr_t)n->data;
          tmp.s_addr = htonl(found_nexthop);
          inet_ntop (AF_INET, &tmp, buf, sizeof(buf));
          printf ("+ Found route for %s: %s\n", key[j], buf);
        }
      else
        {
          printf ("- No route for %s\n", key[j]);
        }
    }

  rib_free (t);

  return 0;
}