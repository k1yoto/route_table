CPU: Intel(R) N100
K=1,2の場合は動作確認済み，K=3以降はまだ

K=1の場合
```sh
$ ./main all
------------------------------------------------
Performance test:
Total 3024721 routes added
Elapsed time: 45.684741 sec for 268435456 lookups
Lookup per second: 5.875823M lookups/sec
```

K=2の場合
```sh
$ ./main all
------------------------------------------------
Performance test:
Total 3024721 routes added
Elapsed time: 32.343849 sec for 268435456 lookups
Lookup per second: 8.299428M lookups/sec
```
