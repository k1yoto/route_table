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
  char line[4096];
  char cider[64];
  char nexthop[64];
  int ret, count = 0;
  uint64_t res, i;
  struct in_addr addr1, addr2;
  int plen;
  double tv1, tv2;
  uint32_t a;

  fp = fopen ("tests/rib.20251001.0000.ipv4.txt", "r");
  if (fp == NULL)
      return -1;

  t = rib_new (t);
  if (t == NULL)
      return -1;

  /* Load the full route */
  while (fgets(line, sizeof(line), fp) != NULL)
    {
      ret = sscanf (line, "%63s %63s", cider, nexthop);
      if (ret < 0)
        return -1;

      plen = inet_net_pton(AF_INET, cider, &addr1, sizeof(addr1));
      if (plen < 0)
        return -1;

      ret = inet_pton (AF_INET, nexthop, &addr2);
      if (ret < 0)
        return -1;

      ret = rib_route_add (t, (const uint8_t *)&addr1, plen, (uint8_t *)&addr2);
      if (ret < 0)
        return -1;

      if (++count % 100000 == 0)
          printf ("Added %d routes\n", count);
    }

  printf ("Total %d routes added\n", count);
  fclose (fp);

  tv1 = gettime ();

  // see: https://github.com/drpnd/radix-tree/blob/master/tests/basic.c
  // Lookup the entire IPv4 address space
  res = 0;
  for ( i = 0; i < 0x10000000ULL; i++ ) {
      a = xor128();
      res ^= (uint64_t)rib_route_lookup (t, (uint8_t *)&a);
  }

  tv2 = gettime ();

  printf ("Elapsed time: %.6f sec\n", tv2 - tv1);
  printf ("Lookup per second: %.2f M lookups/sec\n", 0x10000000ULL / (tv2 - tv1) / 1000000);

  rib_free (t);

  return 0;
}