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

static int
_add (struct rib_node **n, const uint8_t *key, int plen, void *data, int depth, int k, int child_sz)
{
  struct rib_node *new;
  int idx, base, patterns;
  size_t node_size;

  if (*n == NULL)
    {
      node_size = sizeof (struct rib_node) + child_sz * sizeof (struct rib_node *);
      new = malloc (node_size);
      if (!new)
        return -1;
      memset (new, 0, node_size);
      *n = new;
    }
  
  if (plen == depth)
    {
      /* push to all child nodes */
      for (idx = 0; idx < child_sz; idx++)
        {
          if ((*n)->child[idx] == NULL)
            {
              node_size = sizeof(struct rib_node) + child_sz * sizeof(struct rib_node *);
              (*n)->child[idx] = malloc(node_size);
              if (!(*n)->child[idx])
                return -1;
              memset((*n)->child[idx], 0, node_size);
            }
          /* update if more specific or data is NULL */
          if ((*n)->child[idx]->data == NULL || (*n)->child[idx]->plen < plen)
            {
              (*n)->child[idx]->data = data;
              (*n)->child[idx]->plen = plen;
            }
        }
      return 0;
    }
  else if (plen < depth + k)
    {
      base = BIT_INDEX32(key, depth, (plen - depth)) << (k - (plen - depth));
      patterns = 1 << (k - (plen - depth));

      for (int i = 0; i < patterns; i++)
        {
          idx = base | i;
          if ((*n)->child[idx] == NULL)
            {
              node_size = sizeof(struct rib_node) + child_sz * sizeof(struct rib_node *);
              (*n)->child[idx] = malloc(node_size);
              if (!(*n)->child[idx])
                return -1;
              memset((*n)->child[idx], 0, node_size);
            }
          /* update if more specific or data is NULL */
          if ((*n)->child[idx]->data == NULL || (*n)->child[idx]->plen < plen)
            {
              (*n)->child[idx]->data = data;
              (*n)->child[idx]->plen = plen;
            }
        }
      return 0;
    }

  idx = BIT_INDEX32(key, depth, k);
  return _add (&(*n)->child[idx], key, plen, data, depth + k, k, child_sz);
}

int
rib_route_add (struct rib_tree *t, const uint8_t *key, int plen, void *data)
{
  return _add (&t->root, key, plen, data, 0, t->k, t->child_sz);
}

static int
_shrink(struct rib_node **n, int child_sz)
{
    int has_child;

    if ( *n == NULL )
      return 0;

    has_child = 0;
    for (int i = 0; i < child_sz; i++)
      {
        if ((*n)->child[i] != NULL || _shrink(&(*n)->child[i], child_sz))
          has_child = 1;
      }

    if (has_child)
      return 1;
    else
      {
        if ((*n)->data == NULL)
          {
            free(*n);
            *n = NULL;
            return 0;
          }
        else
          return 1;
      }
}

static int
_delete(struct rib_node **n, const uint8_t *key, int plen, int depth, int k, int child_sz)
{
  int idx, base, patterns, found;

  if (*n == NULL)
    return -1;

  if (plen == depth)
    {
      /* delete from all child nodes that match this prefix length */
      found = 0;
      for (idx = 0; idx < child_sz; idx++)
        {
          if ((*n)->child[idx] != NULL &&
              (*n)->child[idx]->data != NULL &&
              (*n)->child[idx]->plen == plen)
            {
              (*n)->child[idx]->data = NULL;
              (*n)->child[idx]->plen = 0;
              found = 1;
            }
        }
      if (found)
        {
          _shrink(n, child_sz);
          return 0;
        }
      else
        return -1;
    }
  else if (plen < depth + k)
    {
      base = BIT_INDEX32(key, depth, (plen - depth)) << (k - (plen - depth));
      patterns = 1 << (k - (plen - depth));

      found = 0;
      for (int i = 0; i < patterns; i++)
        {
          idx = base | i;
          if ((*n)->child[idx] != NULL &&
              (*n)->child[idx]->data != NULL &&
              (*n)->child[idx]->plen == plen)
            {
              (*n)->child[idx]->data = NULL;
              (*n)->child[idx]->plen = 0;
              found = 1;
            }
        }
      if (found)
        {
          _shrink(n, child_sz);
          return 0;
        }
      else
        return -1;
    }

  idx = BIT_INDEX32(key, depth, k);
  return _delete(&(*n)->child[idx], key, plen, depth + k, k, child_sz);
}

int
rib_route_delete(struct rib_tree *t, const uint8_t *key, int plen)
{
  return _delete(&t->root, key, plen, 0, t->k, t->child_sz);
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