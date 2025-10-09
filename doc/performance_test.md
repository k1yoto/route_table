CPU: Intel(R) N100

## 固定配列

K=1
```sh
$ ./main performance
------------------------------------------------
Performance test:
Total 3024721 routes added
Elapsed time: 52.329164 sec for 268435456 lookups
Lookup per second: 5.129749M lookups/sec
```

K=2
```sh
./main performance
------------------------------------------------
Performance test:
Total 3024721 routes added
Elapsed time: 26.962440 sec for 268435456 lookups
Lookup per second: 9.955904M lookups/sec
```

K=3
```sh
$ ./main performance
------------------------------------------------
Performance test:
Total 3024721 routes added
Elapsed time: 22.705480 sec for 268435456 lookups
Lookup per second: 11.822496M lookups/sec
```

K=4
```sh
$ ./main performance
------------------------------------------------
Performance test:
Total 3024721 routes added
Elapsed time: 22.586367 sec for 268435456 lookups
Lookup per second: 11.884844M lookups/sec
```

## 動的配列

K=1
```sh
$ ./main performance 1
------------------------------------------------
Performance test (K=1):
Total 3024721 routes added
Elapsed time: 69.511226 sec for 268435456 lookups
Lookup per second: 3.861757M lookups/sec
```

K=2
```sh
$ ./main performance 2
------------------------------------------------
Performance test (K=2):
Total 3024721 routes added
Elapsed time: 43.384788 sec for 268435456 lookups
Lookup per second: 6.187317M lookups/sec
```

K=3
```sh
$ ./main performance 3
------------------------------------------------
Performance test (K=3):
Total 3024721 routes added
Elapsed time: 31.042257 sec for 268435456 lookups
Lookup per second: 8.647421M lookups/sec
```

K=4
```sh
$ ./main performance 4
------------------------------------------------
Performance test (K=4):
Total 3024721 routes added
Elapsed time: 29.755731 sec for 268435456 lookups
Lookup per second: 9.021303M lookups/sec
```

## Flexible Array Member

K=1
```sh
$ ./main performance 1
------------------------------------------------
Performance test (K=1):
Total 3024721 routes added
Elapsed time: 55.798769 sec for 268435456 lookups
Lookup per second: 4.810777M lookups/sec
```

K=2
```sh
$ ./main performance 2
------------------------------------------------
Performance test (K=2):
Total 3024721 routes added
Elapsed time: 30.171602 sec for 268435456 lookups
Lookup per second: 8.896957M lookups/sec
```

K=3
```sh
$ ./main performance 3
------------------------------------------------
Performance test (K=3):
Total 3024721 routes added
Elapsed time: 25.406111 sec for 268435456 lookups
Lookup per second: 10.565783M lookups/sec
```

K=4
```sh
$ ./main performance 4
------------------------------------------------
Performance test (K=4):
Total 3024721 routes added
Elapsed time: 26.062372 sec for 268435456 lookups
Lookup per second: 10.299732M lookups/sec
```
