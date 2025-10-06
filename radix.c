#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "radix.h"

/* returns true if the b_th bit of key is 1 */
#define BIT_INDEX(key, s, n) ((((uint8_t *)(key))[(s) >> 3] >> (8 - ((s) & 7) - (n))) & ((1 << (n)) - 1))

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
      for (int i = 0; i < 4; i++)
        {
          _free_rib_node (n->child[i]);
        }
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
  int idx, base, patterns;

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
        return 0; /* already exists. temporary 0, to avoid issues with test_performance.*/
      (*n)->data = data;
      return 0;
    }
  else if (plen < depth + 2)
    {
      base = BIT_INDEX(key, depth, (plen - depth)) << (2 - (plen - depth));
      patterns = 1 << (2 - (plen - depth));

      for (int i = 0; i < patterns; i++)
        {
          idx = base | i;
          if ((*n)->child[idx] == NULL)
            {
              (*n)->child[idx] = malloc(sizeof(struct rib_node));
              if (!(*n)->child[idx])
                return -1;
              memset((*n)->child[idx], 0, sizeof(struct rib_node));
            }
          if ((*n)->child[idx]->data != NULL)
            return 0;  /* already exists. temporary 0, to avoid issues with test_performance. */
          (*n)->child[idx]->data = data;
        }
      return 0;
    }

  idx = BIT_INDEX(key, depth, 2);
  return _add (&(*n)->child[idx], key, plen, data, depth + 2 );
}

int
rib_route_add (struct rib_tree *t, const uint8_t *key, int plen, void *data)
{
  return _add (&t->root, key, plen, data, 0);
}

static int
_shrink(struct rib_node **n)
{
    int has_child;

    if ( *n == NULL )
      return 0;

    has_child = 0;
    for (int i = 0; i < 4; i++)
      {
        if ((*n)->child[i] != NULL || _shrink(&(*n)->child[i]))
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
_delete(struct rib_node **n, const uint8_t *key, int plen, int depth)
{
  int idx, base, patterns;

  if (*n == NULL)
    return -1;

  if (plen == depth)
    {
      if ((*n)->data != NULL)
        {
          (*n)->data = NULL;
          _shrink(n);
          return 0;
        }
      else
        return -1;
    }
  else if (plen < depth + 2)
    {
      base = BIT_INDEX(key, depth, (plen - depth)) << (2 - (plen - depth));
      patterns = 1 << (2 - (plen - depth));

      for (int i = 0; i < patterns; i++)
        {
          idx = base | i;
          if ((*n)->child[idx] != NULL && (*n)->child[idx]->data != NULL)
            {
              (*n)->child[idx]->data = NULL;
            }
        }
      _shrink(n);
      return 0;
    }

  idx = BIT_INDEX(key, depth, 2);
  return _delete(&(*n)->child[idx], key, plen, depth + 2);
}

int
rib_route_delete(struct rib_tree *t, const uint8_t *key, int plen)
{
  return _delete(&t->root, key, plen, 0);
}

static struct rib_node *
_lookup (struct rib_node *n, struct rib_node *cand, const uint8_t *key,
         int depth)
{
  int idx;

  if (n == NULL)
    return cand;

  if (n->data != NULL)
    cand = n;

  idx = BIT_INDEX(key, depth, 2);
  return _lookup (n->child[idx], cand, key, depth + 2);
}

struct rib_node *
rib_route_lookup (struct rib_tree *t, const uint8_t *key)
{
  return _lookup (t->root, NULL, key, 0);
}