# 一、socket函数

## 1、头文件：
```c
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
```
## 2、函数原型：

```c
int socket(int domain, int type, int protocol);

socket函数类似于open，用来打开一个网络连接，如果成功则返回一个网络文件描述符（int类型），之后我们操作这个网络连接都通过这个网络文件描述符。

dimain：域，网络域，网络地址范围（IPV4或IPV6等）,也就是协议簇

type：指定套接字类型：SOCK_STREAM（TCP网络）、SOCK_DGRAM（UDP）、SOCK_SEQPACKET

protocol:指定协议，如果指定0，表示使用默认的协议
```

## 3、函数形参：


### 3.1、domain:(域)

```c
AF_INET　　　　  ip

AF_INET6　　　　ipv6

AF_PACKET         packet         低级数据包接口

PF_PACKET　　　不懂，待了解

PF_INET　　　　  待了解(AF开头的表示地址族，PF开头的表示协议族，协议族包含多个地址族，但是当前这种还从未实现，而在<sys/socket.h>中PF的值总是与AF的值相等的)
```

###3.2、type：(套接字类型)：

```c
SOCK_RAW　　  　　原始套接字  　　　——>使用原始套接字时候调用，原始套接字也就是链路层协议

SOCK_STREAM　　  字节流套接字　　  ——>提供顺序，可靠，双向，基于连接的字节流。 可以支持带外数据传输机制。例如：TCP协议、FTP协议

SOCK_DGRAM         数据报套接字　　  ——>支持数据报（无连接，不可靠的固定最大长度的消息）例如：UDP协议

SOCK_SEQPACKET   有序分组套接字    ——>为固定最大长度的数据报提供有序，可靠，双向连接的数据传输路径; 消费者需要利用每个输入系统调用读取整个分组
```

### 3.3、protocol(协议)：

```c
IPPROTO_IP　　　　   IP传输协议

IPPROTO_TCP　　　   TCP传输协议

IPPROTO_UDP　　     UDP协议

IPPROTO_SCTP　　    SCTP传输协议

IPPROTO_ICMP          ICMP协议

IPPROTO_IGMP　　    IGMP协议

一般情况下IPPROTO_TCP、IPPROTO_UDP、IPPROTO_ICMP协议用的最多，UDP协议protocol就取IPPROTO_UDP，TCP协议protocol就取IPPROTO_TCP；一般情况下，我们让protocol等于0就可以，系统会给它默认的协议。但是要是使用raw socket协议，protocol就不能简单设为0，要与type参数匹配.
```

## 4、返回值：

成功时返回一个小的非负整数值，他与文件描述符类似，我们称为套接字描述符，简称sockfd。失败，则返回-1。

## 5、例子：

```c
g_ulDevRawSock = socket( PF_PACKET, SOCK_RAW, htons(ETH_DEV) ); //#define ETH_DEV 0x8607

iFd = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);

fd = socket(PF_INET, SOCK_DGRAM, 0);

dnc_socket = socket(AF_INET, SOCK_STREAM, 0);

pupdate_info->update_socket = socket(PF_PACKET, SOCK_RAW, htons(0x8505)
```

# 二、connect函数

## 1、头文件：
```c
#include <sys/types.h> /* See NOTES */

#include <sys/socket.h>
```
## 2、函数原型：
```
int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

TCP客户端通过connect函数与服务端连接，进行通信。
```
## 3、函数形参：

```c
3.1、sockfd(客户端自己创建的sock)

3.2、addr(服务端地址族、服务端IP地址、服务端端口号)

3.3、addrlen(服务端地址字节长度)
```

## 4、返回值：

连接成功，返回0，连接失败，返回-1

## 5、例子：

```c
seraddr.sin_family = AF_INET; 　　　　// 设置地址族为IPv4

seraddr.sin_port = htons(SERPORT);   // 设置地址的端口号信息

seraddr.sin_addr.s_addr = inet_addr(SERADDR); //　设置IP地址

ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
```

# 三、bind函数

## 1、头文件：
```c
#include <sys/types.h> /* See NOTES */

#include <sys/socket.h>
```

## 2、函数原型：

int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

服务端套接字绑定自己的IP地址与端口号，客户端那边可以不写，内核会给它分配一个临时的端口。

## 3、函数形参：

```c
3.1、sockfd：服务器或者客户端自己创建的socket

3.2、addr:服务器或者客户端自己的地址信息(协议族、IP、端口号)

3.3、addrlen：服务器或者客户端自己的地址信息的长度
```

## 4、返回值：

绑定成功，返回0，失败返回-1

## 5、例子：

```c
seraddr.sin_family = AF_INET; // 设置地址族为IPv4

seraddr.sin_port = htons(SERPORT); // 设置地址的端口号信息

seraddr.sin_addr.s_addr = inet_addr(SERADDR); //　设置IP地址

ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
``` 

# 四、listen函数

## 1、头文件：

```c
#include<sys/socket.h>
```

## 2、函数原型：

int listen(int sockfd, int backlog)

返回： 0——成功，  -1——失败

listen函数一般在调用bind()之后 调用accept()之前使用

## 3、函数形参：

```c
sockfd : 被listen()作用的套接字，在作用之前系统认为用户对这个套接字调用connect函数期待它主动与其它进程连接。作用后，该套接字被转成可以接受外来的连接请求，

backlog : 在处理进程的过程中，可能存在一种半连接的状态，有时由于同时尝试简洁的用户过多，使得服务器进程无法快速完成连接请求。所以建立一个内核维护一个队列跟踪这些完成的连接，但服务器还没有接手处理或正在进行的连接，队列不可过大
```