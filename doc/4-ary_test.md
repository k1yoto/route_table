CPU: Intel(R) N100

```sh
$ ./main all
------------------------------------------------
Performance test:
Total 3024721 routes added
Elapsed time: 32.253078 sec for 268435456 lookups
Lookup per second: 8.322786M lookups/sec
------------------------------------------------
Basic test:
Tree initialized

Lookup: Empty tree
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)

Add: Adding routes
  Added 192.168.1.0/24 -> 10.0.0.1
  Added 192.168.2.0/23 -> 10.0.0.2

Lookup: After adding routes
  192.168.1.10: Found -> 10.0.0.1
  192.168.2.10: Found -> 10.0.0.2
  192.168.3.10: Found -> 10.0.0.2
  1.1.1.1: Not found

Delete: Deleting routes
  Deleted 192.168.1.0/24
  Deleted 192.168.2.0/23

Lookup: After deleting routes
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)

Tree freed
```