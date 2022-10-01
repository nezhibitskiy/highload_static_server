Nginx:
```text
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 100 requests
Completed 200 requests
Completed 300 requests
Completed 400 requests
Completed 500 requests
Completed 600 requests
Completed 700 requests
Completed 800 requests
Completed 900 requests
Completed 1000 requests
Finished 1000 requests


Server Software:        nginx/1.23.1
Server Hostname:        localhost
Server Port:            8082

Document Path:          /wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      1
Time taken for tests:   0.670 seconds
Complete requests:      1000
Failed requests:        0
Total transferred:      955062000 bytes
HTML transferred:       954824000 bytes
Requests per second:    1492.77 [#/sec] (mean)
Time per request:       0.670 [ms] (mean)
Time per request:       0.670 [ms] (mean, across all concurrent requests)
Transfer rate:          1392272.43 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:     1    1   0.1      1       2
Waiting:        0    0   0.0      0       1
Total:          1    1   0.1      1       2

Percentage of the requests served within a certain time (ms)
  50%      1
  66%      1
  75%      1
  80%      1
  90%      1
  95%      1
  98%      1
  99%      1
 100%      2 (longest request)
```

Own server:

```text
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 100 requests
Completed 200 requests
Completed 300 requests
Completed 400 requests
Completed 500 requests
Completed 600 requests
Completed 700 requests
Completed 800 requests
Completed 900 requests
Completed 1000 requests
Finished 1000 requests


Server Software:        nezhibitskiy
Server Hostname:        localhost
Server Port:            8080

Document Path:          /wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      1
Time taken for tests:   3.073 seconds
Complete requests:      1000
Failed requests:        0
Total transferred:      954970000 bytes
HTML transferred:       954824000 bytes
Requests per second:    325.37 [#/sec] (mean)
Time per request:       3.073 [ms] (mean)
Time per request:       3.073 [ms] (mean, across all concurrent requests)
Transfer rate:          303437.51 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       1
Processing:     3    3   0.7      3      15
Waiting:        0    2   0.7      2      14
Total:          3    3   0.7      3      15

Percentage of the requests served within a certain time (ms)
  50%      3
  66%      3
  75%      3
  80%      3
  90%      3
  95%      4
  98%      4
  99%      5
 100%     15 (longest request)
```
