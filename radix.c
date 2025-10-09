#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "radix.h"

// key: byte array, b: bit index
#define BIT_CHECK(key, b) (((uint8_t *)(key))[(b) >> 3] & (0x80 >> ((b) & 0x7)))

// key: address, s: start bit, n: number of bits
static inline uint32_t
BIT_INDEX32(const uint8_t *key, int s, int n)
{
  uint32_t key32 = ((uint32_t)key[0] << 24) |
                   ((uint32_t)key[1] << 16) |
                   ((uint32_t)key[2] << 8)  |
                   ((uint32_t)key[3]);
  return (((uint64_t)(key32) << 32 >> (64 - ((s) + (n)))) & ((1 << (n)) - 1));
}

struct rib_tree
*rib_new (struct rib_tree *t)
{
  if (!t)
    {
      t = malloc (sizeof (struct rib_tree));
      if (!t)
        return NULL;
    }
  t->root = NULL;
  return t;
}

static void
_free_rib_node (struct rib_node *n)
{
  int i;

  if (n != NULL)
    {
      for (i = 0; i < BRANCH_SZ; i++)
        _free_rib_node (n->child[i]);
      free (n);
    }
}

void
rib_free (struct rib_tree *t)
{
  if (t != NULL)
    {
      _free_rib_node (t->root);
      free (t);
    }
}

static int
_add (struct rib_node **n, const uint8_t *key, int plen, void *data, int depth)
{
  struct rib_node *new;
  uint32_t idx, base, first, count, i;

  if (*n == NULL)
    {
      new = malloc (sizeof (struct rib_node));
      if (!new)
        return -1;
      memset (new, 0, sizeof (struct rib_node));
      *n = new;
    }

  if (plen <= depth)
    {
      if ((*n)->valid)
        {
          /* already exists, update data */
          // (*n)->data = data;
          // return 0;
          /* already exists, error */
          return -1;
        }
      (*n)->valid = 1;
      (*n)->data = data;
      return 0;
    }
  else if (plen < depth + K)
    {
      /*
       * (Example: K=2)
       * depth=0
       *   root
       *    |-----00
       *    |-----01
       *    |-----10 <-
       *    |-----11
       *
       * depth=2
       *  root
       *    |-----10
       *           |-----00 child[0]
       *           |-----01 child[1]
       *           |-----10 child[2] <-
       *           |-----11 child[3] <-
       *
       * depth=4
       *  ...
       *
       * plen=3, 101/3
       * -> expand into child[2] and child[3]
       *
       * ------------------------------------
       * base  = 10|1 = 1
       *            ^　determined
       * first = 10|1* = 0b10 = 2
       *             ^ undetermined (K - (plen - depth))
       * count = 10|1*
       *             ^ num of * = 1
       *
       * for (i = 0; i < count; i++)
       *   = first + i: 0b10, 0b11
       * ------------------------------------
       */
      // plen - depth: The number of bits determined in this depth (1 ~ K-1)
      base = BIT_INDEX32 (key, depth, plen - depth);
      // The first child number of the block whose upper take bit matches the base
      first = base << (K - (plen - depth));
      count = 1 << (K - (plen - depth));

      for (i = 0; i < count; i++)
        _add (&(*n)->child[first + i], key, plen, data, depth + K);

      return 0;
    }

  idx = BIT_INDEX32 (key, depth, K);
  _add (&(*n)->child[idx], key, plen, data, depth + K);

  return 0;
}

int
rib_route_add (struct rib_tree *t, const uint8_t *key, int plen, void *data)
{
  return _add (&t->root, key, plen, data, 0);
}

// delete is not implemented

static struct rib_node *
_lookup (struct rib_node *n, struct rib_node *cand, const uint8_t *key,
         int depth)
{
  uint32_t idx;

  if (n == NULL)
    {
      return cand;
    }

  if (n->valid)
    {
      cand = n;
    }

  idx = BIT_INDEX32 (key, depth, K);

  return _lookup(n->child[idx], cand, key, depth + K);
}

struct rib_node *
rib_route_lookup (struct rib_tree *t, const uint8_t *key)
{
  return _lookup (t->root, NULL, key, 0);
}