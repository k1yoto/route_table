## Machine spec
- CPU: 13th Gen Intel(R) Core(TM) i9-13900H
- Mem: 31Gi

### K=2 (4-ary)
```
$ ./main tests/rib.20251001.0000.ipv4.txt
Total 3024721 routes added
Running performance test...
Elapsed time: 15.197938 sec for 268435456 lookups
Lookup per second: 17.662623M lookups/sec
```

```
$ ./main tests/rib.simple.0000.ipv4.txt tests/lookup.address.ipv4.txt
Total 15 routes added
Running basic test with lookup file tests/lookup.address.ipv4.txt...
+ Found route for 192.168.1.10    : 10.0.0.1
+ Found route for 192.168.2.10    : 10.0.0.2
+ Found route for 192.168.3.10    : 10.0.0.2
+ Found route for 1.1.1.1         : 10.5.5.2
+ Found route for 10.0.0.1        : 10.1.1.1
+ Found route for 10.64.0.1       : 10.1.1.2
+ Found route for 10.128.0.1      : 10.1.1.3
+ Found route for 10.192.0.1      : 10.1.1.3
+ Found route for 172.16.0.1      : 10.2.2.1
+ Found route for 172.16.64.1     : 10.2.2.2
+ Found route for 172.16.128.1    : 10.2.2.3
+ Found route for 203.0.113.1     : 10.3.3.1
+ Found route for 203.0.113.129   : 10.3.3.2
+ Found route for 203.0.113.193   : 10.3.3.2
+ Found route for 8.8.8.8         : 10.4.4.1
+ Found route for 15.255.255.255  : 10.4.4.1
+ Found route for 128.0.0.1       : 10.4.4.2
+ Found route for 255.255.255.255 : 10.4.4.2
+ Found route for 198.51.100.42   : 10.5.5.1
+ Found route for 198.51.100.43   : 10.4.4.2
+ Found route for 0.0.0.0         : 10.5.5.2
+ Found route for 127.0.0.1       : 10.5.5.2
```