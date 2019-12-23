[toc]

# 初识brpc

* brpc官方文档  
  <https://github.com/apache/incubator-brpc/blob/master/README_cn.md>
* brpc的功能  
  brpc实现了一套"远程过程调用"网络框架，程序员可以基于这套框架，方便的实现自己的业务逻辑，编程实现server端和client端代码。主要功能包括：  
  * 在一个端口搭建支持多个协议的server;
  * 访问各种协议下的server的client;

* brpc对多协议的支持
  * server端多协议  
  一个端口支持多个协议（百度内部使用的协议(ub/sofa/baidu_std/hulu/nshead等）、http、redis、memcached、thrift等），实现原理：基于一定的规则尝试判断client用的哪种协议。
  * client端多协议  
  client端作为发起端，自然清楚自己的协议格式，同样支持多种协议。  
  * ubrpc及nshead协议  
  ub使用的协议种类很多，但都以nshead作为二进制包的头部，这类服务在brpc中统称为**nshead service**。
  * 官方文档  
  brpc支持的协议： <https://github.com/apache/incubator-brpc/blob/master/docs/cn/new_protocol.md>
  ubrpc和nshead协议： <https://github.com/apache/incubator-brpc/blob/master/docs/cn/nshead_service.md>

# 搭建brpc环境

* 安装依赖  
  <https://github.com/apache/incubator-brpc/blob/master/docs/cn/getting_started.md>  

* 性能测试工具、分析程序中的热点函数  
  <https://github.com/apache/incubator-brpc/blob/master/docs/cn/cpu_profiler.md>   
  <https://blog.csdn.net/10km/article/details/83820080>  

* brpc友好接口——三个用户类
  * Server (server端，创建服务，包含brpc/server.h)
  * Channel(client端，访问服务，包含brpc/channel.h)
  * Controller(调整参数，三类参数Client-side, Server-side和Both-side, 包含brpc/controller.h)

# brpc和braft的关系

* raft协议动图：http://thesecretlivesofdata.com/raft/
* brpc和braft  
  braft是基于brpc的raft协议工业级C++实现，解决服务单点问题，帮助工程师独立实现支持高负载和低延迟的分布式系统。 具体应用：比如一些关键模块的高可用，以及分布式块存储、分布式文件系统、分布式NewSQL系统、分布式文件系统等存储系统。   
  raft已经成为分布式一致性算法的主流，braft中核心的是协议状态机比如log、snapshot、configuration这些东西的抽象和实现。  
  braft是解决复制状态机问题，brpc是解决模块间rpc通信问题。braft中raft协议的互通直接使用brpc实现，runtime使用了bthread。（复制状态机模型：多个节点上，从相同的初始状态开始，执行相同的一串命令，产生相同的最终状态。）  

# brpc实践

// TODO  