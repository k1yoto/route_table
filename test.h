#ifndef TEST_H
#define TEST_H

struct rib_tree *test_load_routes(const char *routes_filename);
int test_basic(struct rib_tree *t, const char *lookup_addrs_filename);
int test_basic_delete(struct rib_tree *t, const char *lookup_addrs_filename, const char *delete_routes_filename);
int test_performance(struct rib_tree *t);

#endif /* TEST_H */