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
test_performance (int k)
{
  struct rib_tree *t = NULL;
  FILE *fp;
  char line[4096], cider[64], nexthop[64];
  int ret, plen, count = 0;
  uint8_t addr1[4];
  uint64_t res, i;
  uint32_t addr2;
  double tv1, tv2;
  struct in_addr tmp;
  uint8_t rand_addr[4];

  printf ("------------------------------------------------\n");
  printf ("Performance test (K=%d):\n", k);

  fp = fopen ("tests/rib.20251001.0000.ipv4.txt", "r");
  if (fp == NULL)
      return -1;

  t = rib_new (k);
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
      uint32_t r = xor128();
      rand_addr[0] = (r >> 24) & 0xFF;
      rand_addr[1] = (r >> 16) & 0xFF;
      rand_addr[2] = (r >> 8) & 0xFF;
      rand_addr[3] = r & 0xFF;
      res ^= (uint64_t)rib_route_lookup (t, rand_addr);
  }

  tv2 = gettime ();

  /* Print the results */
  printf ("Elapsed time: %.6f sec for %llu lookups\n", tv2 - tv1, N);
  printf ("Lookup per second: %.6fM lookups/sec\n", N / (tv2 - tv1) / 1000000);

  rib_free (t);

  return 0;
}

int
test_basic (int k)
{
  struct rib_tree *t = NULL;
  int ret;
  uint8_t addr1[4];
  char buf[64];
  struct rib_node *n;
  uint32_t found_nexthop;
  struct in_addr tmp, addr;

  printf ("------------------------------------------------\n");
  printf ("Basic test (K=%d):\n", k);

  t = rib_new (k);
  if (t == NULL)
      return -1;
  printf ("Tree initialized\n");

  /* route information */
  struct {
      char *prefix;
      char *nexthop;
  } routes[] = {
      {"192.168.1.0/24", "10.0.0.1"},
      {"192.168.2.0/23", "10.0.0.2"},
      /* prefix lengths that cross K-bit boundaries */
      {"10.0.0.0/8", "10.1.1.1"},        /* plen=8: stops before depth 9 */
      {"10.64.0.0/10", "10.1.1.2"},      /* plen=10: crosses first K boundary (depth 9) */
      {"10.128.0.0/9", "10.1.1.3"},      /* plen=9: exactly at first K boundary */
      {"172.16.0.0/12", "10.2.2.1"},     /* plen=12: exactly at depth 12 */
      {"172.16.64.0/18", "10.2.2.2"},    /* plen=18: exactly at depth 18 (K*6) */
      {"172.16.128.0/17", "10.2.2.3"},   /* plen=17: crosses K boundary */
      /* overlapping prefixes for longest prefix matching */
      {"203.0.113.0/24", "10.3.3.1"},    /* /24 */
      {"203.0.113.128/25", "10.3.3.2"},  /* /25 more specific */
      {"203.0.113.192/26", "10.3.3.3"},  /* /26 even more specific */
      /* short prefix test */
      {"8.0.0.0/5", "10.4.4.1"},         /* plen=5: within first K bits */
      {"128.0.0.0/1", "10.4.4.2"},       /* plen=1: single bit */
      /* edge case: plen=32 */
      {"198.51.100.42/32", "10.5.5.1"},  /* host route */
      {"0.0.0.0/0", "10.5.5.2"},         /* plen=0: default route */
  };
  int num_routes = sizeof(routes) / sizeof(routes[0]);

  /* lookup addresses */
  char *lookup_addrs[] = {
      "192.168.1.10",      /* 10.0.0.1 */
      "192.168.2.10",      /* 10.0.0.2 */
      "192.168.3.10",      /* 10.0.0.2 */
      "1.1.1.1",           /* 10.5.5.2 */
      /* boundary test */
      "10.0.0.1",          /* 10.1.1.1 */
      "10.64.0.1",         /* 10.1.1.2 (more specific than /8) */
      "10.128.0.1",        /* 10.1.1.3 (more specific than /8) */
      "10.192.0.1",        /* 10.1.1.3 */
      "172.16.0.1",        /* 10.2.2.1 */
      "172.16.64.1",       /* 10.2.2.2 (more specific) */
      "172.16.128.1",      /* 10.2.2.3 (more specific) */
      /* longest prefix matching */
      "203.0.113.1",       /* 10.3.3.1 */
      "203.0.113.129",     /* 10.3.3.2 */
      "203.0.113.193",     /* 10.3.3.3 (most specific) */
      /* short prefix test */
      "8.8.8.8",           /* 10.4.4.1 */
      "15.255.255.255",    /* 10.4.4.1 */
      "128.0.0.1",         /* 10.4.4.2 */
      "255.255.255.255",   /* 10.4.4.2 */
      /* host route test */
      "198.51.100.42",     /* 10.5.5.1 */
      "198.51.100.43",     /* 10.4.4.2 */
      "0.0.0.0",           /* 10.5.5.2 (default) */
      "127.0.0.1",         /* 10.5.5.2 (default) */
  };
  int num_tests = sizeof(lookup_addrs) / sizeof(lookup_addrs[0]);

  printf ("\nLookup: Empty tree\n");
  for (int i = 0; i < num_tests; i++)
    {
      ret = inet_pton (AF_INET, lookup_addrs[i], &addr);
      if (ret < 0)
          return -1;
      uint8_t lookup_addr[4];
      lookup_addr[0] = (addr.s_addr >> 0) & 0xFF;
      lookup_addr[1] = (addr.s_addr >> 8) & 0xFF;
      lookup_addr[2] = (addr.s_addr >> 16) & 0xFF;
      lookup_addr[3] = (addr.s_addr >> 24) & 0xFF;
      n = rib_route_lookup (t, lookup_addr);
      if (n)
          printf ("  %s: Found (unexpected)\n", lookup_addrs[i]);
      else
          printf ("  %s: Not found (expected)\n", lookup_addrs[i]);
    }

  printf ("\nAdd: Adding routes\n");
  for (int i = 0; i < num_routes; i++)
    {
      int plen = inet_net_pton(AF_INET, routes[i].prefix, addr1, sizeof(addr1));
      if (plen < 0)
          return -1;

      ret = inet_pton (AF_INET, routes[i].nexthop, &tmp);
      if (ret < 0)
          return -1;
      uint32_t nexthop = ntohl(tmp.s_addr);

      ret = rib_route_add (t, addr1, plen, (void *)(uintptr_t)nexthop);
      if (ret < 0)
        {
          printf ("  Failed to add %s\n", routes[i].prefix);
          return -1;
        }
      printf ("  Added %s -> %s\n", routes[i].prefix, routes[i].nexthop);
    }

  printf ("\nLookup: After adding routes\n");
  for (int i = 0; i < num_tests; i++)
    {
      ret = inet_pton (AF_INET, lookup_addrs[i], &addr);
      if (ret < 0)
          return -1;
      uint8_t lookup_addr[4];
      lookup_addr[0] = (addr.s_addr >> 0) & 0xFF;
      lookup_addr[1] = (addr.s_addr >> 8) & 0xFF;
      lookup_addr[2] = (addr.s_addr >> 16) & 0xFF;
      lookup_addr[3] = (addr.s_addr >> 24) & 0xFF;
      n = rib_route_lookup (t, lookup_addr);
      if (n)
        {
          found_nexthop = (uint32_t)(uintptr_t)n->data;
          tmp.s_addr = htonl(found_nexthop);
          inet_ntop (AF_INET, &tmp, buf, sizeof(buf));
          printf ("  %s: Found -> %s\n", lookup_addrs[i], buf);
        }
      else
        {
          printf ("  %s: Not found\n", lookup_addrs[i]);
        }
    }

  printf ("\nDelete: Deleting routes\n");
  for (int i = 0; i < num_routes; i++)
    {
      int plen = inet_net_pton(AF_INET, routes[i].prefix, addr1, sizeof(addr1));
      if (plen < 0)
          return -1;

      ret = rib_route_delete (t, addr1, plen);
      if (ret < 0)
          printf ("  Failed to delete %s\n", routes[i].prefix);
      else
          printf ("  Deleted %s\n", routes[i].prefix);
    }

  printf ("\nLookup: After deleting routes\n");
  for (int i = 0; i < num_tests; i++)
    {
      ret = inet_pton (AF_INET, lookup_addrs[i], &addr);
      if (ret < 0)
          return -1;
      uint8_t lookup_addr[4];
      lookup_addr[0] = (addr.s_addr >> 0) & 0xFF;
      lookup_addr[1] = (addr.s_addr >> 8) & 0xFF;
      lookup_addr[2] = (addr.s_addr >> 16) & 0xFF;
      lookup_addr[3] = (addr.s_addr >> 24) & 0xFF;
      n = rib_route_lookup (t, lookup_addr);
      if (n)
          printf ("  %s: Found (unexpected)\n", lookup_addrs[i]);
      else
          printf ("  %s: Not found (expected)\n", lookup_addrs[i]);
    }

  rib_free (t);
  printf ("\nTree freed\n");

  return 0;
}