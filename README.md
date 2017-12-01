# HttpServer
<p>此版本为<a href="https://github.com/lovercode/WebServer.git">WebServer</a>的改进版，之前的WebServer写的太挫了（虽然这个也很挫）</p>

### 基本思路
<img src="img/server.png">

### 目录说明
    cl_accept_task.h        接受请求的任务，直接添加到线程池的任务队列
    cl_base_task.h          用于线程池的任务队列调用的任务对象，类似基类的概念，其他任务（如接受请求的任务）想要能被线程池调用，就必须包含此对象
    cl_event.h              事件对象，epoll实现，如果一个事件想要被此对象监听，需要包含其中的cl_event_node结构体，当此对象中监听的事件发生，会把事件节点cl_event_node的任务指针指向的任务添加到线程池
    cl_http_event.h         http处理事件和处理任务的封装
    cl_link.h               通用链表
    cl_pthread_pool.h       线程池，所有线程阻塞在一个条件变量，等待任务到来，当任务到来后会调用任务的回调函数
    cl_socket.h             对socket的封装，每个socket会有两个共享内存映射，主要是作为发送数据和接受数据的缓冲区
    main.h                  主函数


### ab性能测试：

    codelover@codelover ~$ ab -c 1000 -n 10000 http://127.0.0.1:7777/index.html
    This is ApacheBench, Version 2.3 <$Revision: 1796539 $>
    Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
    Licensed to The Apache Software Foundation, http://www.apache.org/

    Benchmarking 127.0.0.1 (be patient)
    Completed 1000 requests
    Completed 2000 requests
    Completed 3000 requests
    Completed 4000 requests
    Completed 5000 requests
    Completed 6000 requests
    Completed 7000 requests
    Completed 8000 requests
    Completed 9000 requests
    Completed 10000 requests
    Finished 10000 requests


    Server Software:        Codelover
    Server Hostname:        127.0.0.1
    Server Port:            7777

    Document Path:          /index.html
    Document Length:        916 bytes

    Concurrency Level:      1000
    Time taken for tests:   1.276 seconds
    Complete requests:      10000
    Failed requests:        0
    Total transferred:      10240000 bytes
    HTML transferred:       9160000 bytes
    Requests per second:    7837.11 [#/sec] (mean)
    Time per request:       127.598 [ms] (mean)
    Time per request:       0.128 [ms] (mean, across all concurrent requests)
    Transfer rate:          7837.11 [Kbytes/sec] received

    Connection Times (ms)
                  min  mean[+/-sd] median   max
    Connect:       12   49  70.0     41    1053
    Processing:    11   47  15.9     44     236
    Waiting:        7   27  15.3     22     226
    Total:         55   96  70.9     87    1097

    Percentage of the requests served within a certain time (ms)
      50%     87
      66%     96
      75%    101
      80%    108
      90%    118
      95%    148
      98%    160
      99%    162
     100%   1097 (longest request)


### 目前情况：
    目前还没实现http协议，用ab工具测试了下并发情况如上
