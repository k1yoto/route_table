#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "radix.h"

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
*rib_new (int k)
{
  struct rib_tree *t;

  if (k <= 0 || k > 8)
    return NULL;

  t = malloc (sizeof (struct rib_tree));
  if (!t)
    return NULL;

  t->root = NULL;
  t->k = k;
  t->child_sz = 1 << k;
  return t;
}

static void
_free_rib_node (struct rib_node *n, int child_sz)
{
  if (n != NULL)
    {
      for (int i = 0; i < child_sz; i++)
        {
          _free_rib_node (n->child[i], child_sz);
        }
      free (n);
    }
}

void
rib_free (struct rib_tree *t)
{
  if (t != NULL)
    {
      _free_rib_node (t->root, t->child_sz);
      free (t);
    }
}

static struct rib_node *
_add (struct rib_node *n, const uint8_t *key, int plen, void *data, int depth, int k, int child_sz, int is_leaf)
{
  int idx, base, patterns;
  size_t node_size;

  if (n == NULL)
    {
      node_size = sizeof (struct rib_node) + child_sz * sizeof (struct rib_node *);
      n = malloc (node_size);
      if (!n)
        return NULL;
      memset (n, 0, node_size);
    }

  if (is_leaf)
    {
      if (n->data == NULL || n->plen < plen)
        {
          n->data = data;
          n->plen = plen;
        }
      return n;
    }
  
  if (plen == depth)
    {
      /* push to all child nodes */
      for (idx = 0; idx < child_sz; idx++)
        {
          n->child[idx] = _add (n->child[idx], key, plen, data, depth + k, k, child_sz, 1);
          if (n->child[idx] == NULL)
            return NULL;
        }
      return n;
    }
  else if (plen < depth + k)
    {
      base = BIT_INDEX32(key, depth, (plen - depth)) << (k - (plen - depth));
      patterns = 1 << (k - (plen - depth));

      for (int i = 0; i < patterns; i++)
        {
          idx = base | i;
          n->child[idx] = _add (n->child[idx], key, plen, data, depth + k, k, child_sz, 1);
          if (n->child[idx] == NULL)
            return NULL;
        }
      return n;
    }

  idx = BIT_INDEX32(key, depth, k);
  n->child[idx] = _add (n->child[idx], key, plen, data, depth + k, k, child_sz, 0);
  if (n->child[idx] == NULL)
    return NULL;

  return n;
}

int
rib_route_add (struct rib_tree *t, const uint8_t *key, int plen, void *data)
{
  t->root = _add (t->root, key, plen, data, 0, t->k, t->child_sz, 0);
  return (t->root == NULL) ? -1 : 0;
}

static struct rib_node *
_shrink(struct rib_node *n, int child_sz)
{
    if (n == NULL)
      return NULL;

    for (int i = 0; i < child_sz; i++)
      {
        if (n->child[i] != NULL)
          return n;
      }

    if (n->data == NULL)
      {
        free (n);
        return NULL;
      }

    return n;
}

static struct rib_node *
_delete(struct rib_node *n, const uint8_t *key, int plen, int depth, int k, int child_sz, int is_leaf, int *found)
{
  int idx, base, patterns;

  if (n == NULL)
    return NULL;

  if (is_leaf)
    {
      if (n->data != NULL && n->plen == plen)
        {
          n->data = NULL;
          n->plen = 0;
          *found = 1;
        }
      return n;
    }

  if (plen == depth)
    {
      /* delete from all child nodes that match this prefix length */
      for (idx = 0; idx < child_sz; idx++)
        n->child[idx] = _delete (n->child[idx], key, plen, depth + k, k, child_sz, 1, found);
      return _shrink (n, child_sz);
    }
  else if (plen < depth + k)
    {
      base = BIT_INDEX32(key, depth, (plen - depth)) << (k - (plen - depth));
      patterns = 1 << (k - (plen - depth));

      for (int i = 0; i < patterns; i++)
        {
          idx = base | i;
          n->child[idx] = _delete (n->child[idx], key, plen, depth + k, k, child_sz, 1, found);
        }
      return _shrink (n, child_sz);
    }

  idx = BIT_INDEX32(key, depth, k);
  n->child[idx] = _delete(n->child[idx], key, plen, depth + k, k, child_sz, 0, found);
  return _shrink (n, child_sz);
}

int
rib_route_delete(struct rib_tree *t, const uint8_t *key, int plen)
{
  int found = 0;
  t->root = _delete(t->root, key, plen, 0, t->k, t->child_sz, 0, &found);
  return found ? 0 : -1;
}

static struct rib_node *
_lookup (struct rib_node *n, struct rib_node *cand, const uint8_t *key,
         int depth, int k)
{
  int idx;

  if (n == NULL)
    return cand;

  if (n->data != NULL)
    cand = n;

  idx = BIT_INDEX32(key, depth, k);
  return _lookup (n->child[idx], cand, key, depth + k, k);
}

struct rib_node *
rib_route_lookup (struct rib_tree *t, const uint8_t *key)
{
  return _lookup (t->root, NULL, key, 0, t->k);
}