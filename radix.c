#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "radix.h"

/* returns true if the b_th bit of key is 1 */
#define BIT_CHECK(key, b) (((uint8_t *)(key))[(b) >> 3] & (0x80 >> ((b) & 0x7)))

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
_add (struct rib_node **n, const char *key, int plen, char *data, int depth)
{
  struct rib_node *new;

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

  if (BIT_CHECK (key, depth))
    {
      /* right */
      _add (&(*n)->child[1], key, plen, data, depth + 1);
    }
  else
    {
      /* left */
      _add (&(*n)->child[0], key, plen, data, depth + 1);
    }

  return 0;
}

int
rib_route_add (struct rib_tree *t, const char *key, int plen, char *data)
{
  return _add (&t->root, key, plen, data, 0);
}

// delete

static struct rib_node *
_lookup (struct rib_node *n, struct rib_node *cand, const char *key,
         int depth)
{
  if (n == NULL)
    {
      return cand;
    }

  if (n->data != NULL)
    {
      cand = n;
    }

  if (BIT_CHECK (key, depth))
    {
      /* right */
      return _lookup (n->child[1], cand, key, depth + 1);
    }
  else
    {
      /* left */
      return _lookup (n->child[0], cand, key, depth + 1);
    }
}

struct rib_node *
rib_route_lookup (struct rib_tree *t, const char *key)
{
  return _lookup (t->root, NULL, key, 0);
}