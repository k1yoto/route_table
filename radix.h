#ifndef RADIX_H
#define RADIX_H

struct rib_node
{
  struct rib_node *child[4];
  int valid;
  void *data;
};

struct rib_tree
{
  struct rib_node *root;
};

struct rib_tree *rib_new (struct rib_tree *t);
void rib_free (struct rib_tree *t);
int rib_route_add (struct rib_tree *t, const uint8_t *key, int plen, void *data);
struct rib_node * rib_route_lookup (struct rib_tree *t, const uint8_t *key);

#endif /* RADIX_H */