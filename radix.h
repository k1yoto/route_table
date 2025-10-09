#ifndef RADIX_H
#define RADIX_H

struct rib_node
{
  int plen;
  char *data;
  struct rib_node *child[];
};

struct rib_tree
{
  struct rib_node *root;
  int k;
  int child_sz;
};

struct rib_tree *rib_new (int k);
void rib_free (struct rib_tree *t);
int rib_route_add (struct rib_tree *t, const uint8_t *key, int plen, void *data);
int rib_route_delete (struct rib_tree *t, const uint8_t *key, int plen);
struct rib_node * rib_route_lookup (struct rib_tree *t, const uint8_t *key);

#endif /* RADIX_H */