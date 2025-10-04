#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "radix.h"

// key: byte array, b: bit index
#define BIT_CHECK(key, b) (((uint8_t *)(key))[(b) >> 3] & (0x80 >> ((b) & 0x7)))
// key: address, s: start bit, n: number of bits
#define BIT_INDEX(key, s, n) (((uint64_t)(key) << 32 >> (64 - ((s) + (n)))) & ((1 << (n)) - 1))

#define K 2
#define BRANCHNUM (1 << K)
/*
 * 00, 01, 10, 11 で小ノードを分木
 */

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
  if (n != NULL)
    {
      _free_rib_node (n->child[0]);
      _free_rib_node (n->child[1]);
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
  uint32_t idx, base, first, count, offset;

  if (*n == NULL)
    {
      new = malloc (sizeof (struct rib_node));
      if (!new)
        return -1;
      memset (new, 0, sizeof (struct rib_node));
      *n = new;
    }

  if (plen == depth)
    {
      if ((*n)->data != NULL)
        {
          /* already exists */
          return -1;
        }
      (*n)->data = data;
      return 0;
    }
  else if (plen < depth + K)
    {
      /*
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
       */
      base = BIT_INDEX (key, depth, plen - depth);
      first = base << (K - (plen - depth));
      count = 1 << (K - (plen - depth));

      for (offset = 0; offset < count; offset ++)
        _add (&(*n)->child[first + offset], key, plen, data, plen);

      return 0;
    }

  idx = BIT_INDEX(key, depth, K);
  _add (&(*n)->child[idx], key, plen, data, depth + K);

  return 0;
}

int
rib_route_add (struct rib_tree *t, const uint8_t *key, int plen, void *data)
{
  return _add (&t->root, key, plen, data, 0);
}

// delete

static struct rib_node *
_lookup (struct rib_node *n, struct rib_node *cand, const uint8_t *key,
         int depth)
{
  uint32_t idx;

  if (n == NULL)
    {
      return cand;
    }

  if (n->data != NULL)
    {
      cand = n;
    }

   idx = BIT_INDEX(key, depth, K);

   return _lookup(n->child[idx], cand, key, depth + K);
}

struct rib_node *
rib_route_lookup (struct rib_tree *t, const uint8_t *key)
{
  return _lookup (t->root, NULL, key, 0);
}