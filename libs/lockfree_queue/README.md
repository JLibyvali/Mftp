# Overview

# A Lock-free Queue based CAS  

Pre-knowledge:  
* https://mp.weixin.qq.com/s?__biz=MjM5NjQ5MTI5OA==&mid=2651778446&idx=1&sn=44306b644777a4d939730e7774071541&scene=21#wechat_redirect:~:text=%E7%9A%84%E5%90%8C%E6%AD%A5%E6%9C%BA%E5%88%B6%E3%80%82-,2.8.2%20%E4%BB%80%E4%B9%88%E6%98%AFlock%2Dfree,-lock%2Dfree%E6%B2%A1%E6%9C%89 

* https://jbseg.medium.com/lock-free-queues-e48de693654b

* https://www.lenshood.dev/2021/04/19/lock-free-ring-buffer/#%E6%80%A7%E8%83%BD%E6%B5%8B%E8%AF%95

# The Scalable Lock Free Ring Buffer  

Essay: https://drops.dagstuhl.de/storage/00lipics/lipics-vol146-disc2019/LIPIcs.DISC.2019.28/LIPIcs.DISC.2019.28.pdf  


# TODO 
[] LockFree Queue Destructor, Maybe look: https://www.boost.org/doc/libs/1_87_0/boost/lockfree/queue.hpp, and: https://blog.csdn.net/davidhopper/article/details/131660163. Using `free list or reference count` to track unused node.

