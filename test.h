#ifndef TEST_H
#define TEST_H

struct rib_tree *test_load_routes (const char *filename);
int test_performance (struct rib_tree *t);
int test_basic (struct rib_tree *t, const char *filename);

#endif /* TEST_H */