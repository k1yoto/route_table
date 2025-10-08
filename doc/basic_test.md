CPU: Intel(R) N100

<details><summary>K=1</summary>

```sh
------------------------------------------------
Basic test:
Tree initialized

Lookup: Empty tree
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Add: Adding routes
  Added 192.168.1.0/24 -> 10.0.0.1
  Added 192.168.2.0/23 -> 10.0.0.2
  Added 10.0.0.0/8 -> 10.1.1.1
  Added 10.64.0.0/10 -> 10.1.1.2
  Added 10.128.0.0/9 -> 10.1.1.3
  Added 172.16.0.0/12 -> 10.2.2.1
  Added 172.16.64.0/18 -> 10.2.2.2
  Added 172.16.128.0/17 -> 10.2.2.3
  Added 203.0.113.0/24 -> 10.3.3.1
  Added 203.0.113.128/25 -> 10.3.3.2
  Added 203.0.113.192/26 -> 10.3.3.3
  Added 8.0.0.0/5 -> 10.4.4.1
  Added 128.0.0.0/1 -> 10.4.4.2
  Added 198.51.100.42/32 -> 10.5.5.1
  Added 0.0.0.0/0 -> 10.5.5.2

Lookup: After adding routes
  192.168.1.10: Found -> 10.0.0.1
  192.168.2.10: Found -> 10.0.0.2
  192.168.3.10: Found -> 10.0.0.2
  1.1.1.1: Found -> 10.5.5.2
  10.0.0.1: Found -> 10.1.1.1
  10.64.0.1: Found -> 10.1.1.2
  10.128.0.1: Found -> 10.1.1.3
  10.192.0.1: Found -> 10.1.1.3
  172.16.0.1: Found -> 10.2.2.1
  172.16.64.1: Found -> 10.2.2.2
  172.16.128.1: Found -> 10.2.2.3
  203.0.113.1: Found -> 10.3.3.1
  203.0.113.129: Found -> 10.3.3.2
  203.0.113.193: Found -> 10.3.3.3
  8.8.8.8: Found -> 10.4.4.1
  15.255.255.255: Found -> 10.4.4.1
  128.0.0.1: Found -> 10.4.4.2
  255.255.255.255: Found -> 10.4.4.2
  198.51.100.42: Found -> 10.5.5.1
  198.51.100.43: Found -> 10.4.4.2
  0.0.0.0: Found -> 10.5.5.2
  127.0.0.1: Found -> 10.5.5.2

Delete: Deleting routes
  Deleted 192.168.1.0/24
  Deleted 192.168.2.0/23
  Deleted 10.0.0.0/8
  Deleted 10.64.0.0/10
  Deleted 10.128.0.0/9
  Deleted 172.16.0.0/12
  Deleted 172.16.64.0/18
  Deleted 172.16.128.0/17
  Deleted 203.0.113.0/24
  Deleted 203.0.113.128/25
  Deleted 203.0.113.192/26
  Deleted 8.0.0.0/5
  Deleted 128.0.0.0/1
  Deleted 198.51.100.42/32
  Deleted 0.0.0.0/0

Lookup: After deleting routes
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Tree freed
```

</details>

<details><summary>K=2</summary>

```sh
------------------------------------------------
Basic test:
Tree initialized

Lookup: Empty tree
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Add: Adding routes
  Added 192.168.1.0/24 -> 10.0.0.1
  Added 192.168.2.0/23 -> 10.0.0.2
  Added 10.0.0.0/8 -> 10.1.1.1
  Added 10.64.0.0/10 -> 10.1.1.2
  Added 10.128.0.0/9 -> 10.1.1.3
  Added 172.16.0.0/12 -> 10.2.2.1
  Added 172.16.64.0/18 -> 10.2.2.2
  Added 172.16.128.0/17 -> 10.2.2.3
  Added 203.0.113.0/24 -> 10.3.3.1
  Added 203.0.113.128/25 -> 10.3.3.2
  Added 203.0.113.192/26 -> 10.3.3.3
  Added 8.0.0.0/5 -> 10.4.4.1
  Added 128.0.0.0/1 -> 10.4.4.2
  Added 198.51.100.42/32 -> 10.5.5.1
  Added 0.0.0.0/0 -> 10.5.5.2

Lookup: After adding routes
  192.168.1.10: Found -> 10.0.0.1
  192.168.2.10: Found -> 10.0.0.2
  192.168.3.10: Found -> 10.0.0.2
  1.1.1.1: Found -> 10.5.5.2
  10.0.0.1: Found -> 10.1.1.1
  10.64.0.1: Found -> 10.1.1.2
  10.128.0.1: Found -> 10.1.1.3
  10.192.0.1: Found -> 10.1.1.3
  172.16.0.1: Found -> 10.2.2.1
  172.16.64.1: Found -> 10.2.2.2
  172.16.128.1: Found -> 10.2.2.3
  203.0.113.1: Found -> 10.3.3.1
  203.0.113.129: Found -> 10.3.3.2
  203.0.113.193: Found -> 10.3.3.3
  8.8.8.8: Found -> 10.4.4.1
  15.255.255.255: Found -> 10.4.4.1
  128.0.0.1: Found -> 10.4.4.2
  255.255.255.255: Found -> 10.4.4.2
  198.51.100.42: Found -> 10.5.5.1
  198.51.100.43: Found -> 10.4.4.2
  0.0.0.0: Found -> 10.5.5.2
  127.0.0.1: Found -> 10.5.5.2

Delete: Deleting routes
  Deleted 192.168.1.0/24
  Deleted 192.168.2.0/23
  Deleted 10.0.0.0/8
  Deleted 10.64.0.0/10
  Deleted 10.128.0.0/9
  Deleted 172.16.0.0/12
  Deleted 172.16.64.0/18
  Deleted 172.16.128.0/17
  Deleted 203.0.113.0/24
  Deleted 203.0.113.128/25
  Deleted 203.0.113.192/26
  Deleted 8.0.0.0/5
  Deleted 128.0.0.0/1
  Deleted 198.51.100.42/32
  Deleted 0.0.0.0/0

Lookup: After deleting routes
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Tree freed
```

</details>

<details><summary>K=3</summary>

```sh
------------------------------------------------
Basic test:
Tree initialized

Lookup: Empty tree
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Add: Adding routes
  Added 192.168.1.0/24 -> 10.0.0.1
  Added 192.168.2.0/23 -> 10.0.0.2
  Added 10.0.0.0/8 -> 10.1.1.1
  Added 10.64.0.0/10 -> 10.1.1.2
  Added 10.128.0.0/9 -> 10.1.1.3
  Added 172.16.0.0/12 -> 10.2.2.1
  Added 172.16.64.0/18 -> 10.2.2.2
  Added 172.16.128.0/17 -> 10.2.2.3
  Added 203.0.113.0/24 -> 10.3.3.1
  Added 203.0.113.128/25 -> 10.3.3.2
  Added 203.0.113.192/26 -> 10.3.3.3
  Added 8.0.0.0/5 -> 10.4.4.1
  Added 128.0.0.0/1 -> 10.4.4.2
  Added 198.51.100.42/32 -> 10.5.5.1
  Added 0.0.0.0/0 -> 10.5.5.2

Lookup: After adding routes
  192.168.1.10: Found -> 10.0.0.1
  192.168.2.10: Found -> 10.0.0.2
  192.168.3.10: Found -> 10.0.0.2
  1.1.1.1: Found -> 10.5.5.2
  10.0.0.1: Found -> 10.1.1.1
  10.64.0.1: Found -> 10.1.1.2
  10.128.0.1: Found -> 10.1.1.3
  10.192.0.1: Found -> 10.1.1.3
  172.16.0.1: Found -> 10.2.2.1
  172.16.64.1: Found -> 10.2.2.2
  172.16.128.1: Found -> 10.2.2.3
  203.0.113.1: Found -> 10.3.3.1
  203.0.113.129: Found -> 10.3.3.2
  203.0.113.193: Found -> 10.3.3.3
  8.8.8.8: Found -> 10.4.4.1
  15.255.255.255: Found -> 10.4.4.1
  128.0.0.1: Found -> 10.4.4.2
  255.255.255.255: Found -> 10.4.4.2
  198.51.100.42: Found -> 10.5.5.1
  198.51.100.43: Found -> 10.4.4.2
  0.0.0.0: Found -> 10.5.5.2
  127.0.0.1: Found -> 10.5.5.2

Delete: Deleting routes
  Deleted 192.168.1.0/24
  Deleted 192.168.2.0/23
  Deleted 10.0.0.0/8
  Deleted 10.64.0.0/10
  Deleted 10.128.0.0/9
  Deleted 172.16.0.0/12
  Deleted 172.16.64.0/18
  Deleted 172.16.128.0/17
  Deleted 203.0.113.0/24
  Deleted 203.0.113.128/25
  Deleted 203.0.113.192/26
  Deleted 8.0.0.0/5
  Deleted 128.0.0.0/1
  Deleted 198.51.100.42/32
  Deleted 0.0.0.0/0

Lookup: After deleting routes
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Tree freed
```

</details>

<details><summary>K=4</summary>

```sh
------------------------------------------------
Basic test:
Tree initialized

Lookup: Empty tree
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Add: Adding routes
  Added 192.168.1.0/24 -> 10.0.0.1
  Added 192.168.2.0/23 -> 10.0.0.2
  Added 10.0.0.0/8 -> 10.1.1.1
  Added 10.64.0.0/10 -> 10.1.1.2
  Added 10.128.0.0/9 -> 10.1.1.3
  Added 172.16.0.0/12 -> 10.2.2.1
  Added 172.16.64.0/18 -> 10.2.2.2
  Added 172.16.128.0/17 -> 10.2.2.3
  Added 203.0.113.0/24 -> 10.3.3.1
  Added 203.0.113.128/25 -> 10.3.3.2
  Added 203.0.113.192/26 -> 10.3.3.3
  Added 8.0.0.0/5 -> 10.4.4.1
  Added 128.0.0.0/1 -> 10.4.4.2
  Added 198.51.100.42/32 -> 10.5.5.1
  Added 0.0.0.0/0 -> 10.5.5.2

Lookup: After adding routes
  192.168.1.10: Found -> 10.0.0.1
  192.168.2.10: Found -> 10.0.0.2
  192.168.3.10: Found -> 10.0.0.2
  1.1.1.1: Found -> 10.5.5.2
  10.0.0.1: Found -> 10.1.1.1
  10.64.0.1: Found -> 10.1.1.2
  10.128.0.1: Found -> 10.1.1.3
  10.192.0.1: Found -> 10.1.1.3
  172.16.0.1: Found -> 10.2.2.1
  172.16.64.1: Found -> 10.2.2.2
  172.16.128.1: Found -> 10.2.2.3
  203.0.113.1: Found -> 10.3.3.1
  203.0.113.129: Found -> 10.3.3.2
  203.0.113.193: Found -> 10.3.3.3
  8.8.8.8: Found -> 10.4.4.1
  15.255.255.255: Found -> 10.4.4.1
  128.0.0.1: Found -> 10.4.4.2
  255.255.255.255: Found -> 10.4.4.2
  198.51.100.42: Found -> 10.5.5.1
  198.51.100.43: Found -> 10.4.4.2
  0.0.0.0: Found -> 10.5.5.2
  127.0.0.1: Found -> 10.5.5.2

Delete: Deleting routes
  Deleted 192.168.1.0/24
  Deleted 192.168.2.0/23
  Deleted 10.0.0.0/8
  Deleted 10.64.0.0/10
  Deleted 10.128.0.0/9
  Deleted 172.16.0.0/12
  Deleted 172.16.64.0/18
  Deleted 172.16.128.0/17
  Deleted 203.0.113.0/24
  Deleted 203.0.113.128/25
  Deleted 203.0.113.192/26
  Deleted 8.0.0.0/5
  Deleted 128.0.0.0/1
  Deleted 198.51.100.42/32
  Deleted 0.0.0.0/0

Lookup: After deleting routes
  192.168.1.10: Not found (expected)
  192.168.2.10: Not found (expected)
  192.168.3.10: Not found (expected)
  1.1.1.1: Not found (expected)
  10.0.0.1: Not found (expected)
  10.64.0.1: Not found (expected)
  10.128.0.1: Not found (expected)
  10.192.0.1: Not found (expected)
  172.16.0.1: Not found (expected)
  172.16.64.1: Not found (expected)
  172.16.128.1: Not found (expected)
  203.0.113.1: Not found (expected)
  203.0.113.129: Not found (expected)
  203.0.113.193: Not found (expected)
  8.8.8.8: Not found (expected)
  15.255.255.255: Not found (expected)
  128.0.0.1: Not found (expected)
  255.255.255.255: Not found (expected)
  198.51.100.42: Not found (expected)
  198.51.100.43: Not found (expected)
  0.0.0.0: Not found (expected)
  127.0.0.1: Not found (expected)

Tree freed
```

</details>