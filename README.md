```text
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient).....done


Server Software:        nezhibitskiy
Server Hostname:        localhost
Server Port:            80

Document Path:          /
Document Length:        954824 bytes

Concurrency Level:      10
Time taken for tests:   2.144 seconds
Complete requests:      100
Failed requests:        0
Total transferred:      95497000 bytes
HTML transferred:       95482400 bytes
Requests per second:    46.64 [#/sec] (mean)
Time per request:       214.396 [ms] (mean)
Time per request:       21.440 [ms] (mean, across all concurrent requests)
Transfer rate:          43498.42 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       0
Processing:    64  205 167.9    141     660
Waiting:       62  136 159.7     68     631
Total:         64  205 167.9    141     660

Percentage of the requests served within a certain time (ms)
  50%    141
  66%    204
  75%    255
  80%    322
  90%    398
  95%    660
  98%    660
  99%    660
 100%    660 (longest request)
```