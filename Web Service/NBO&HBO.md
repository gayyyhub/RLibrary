## 大小端及网络字节序

大端字节序（Big Endian）：最高有效位存于最低内存地址处，最低有效位存于最高内存处； 

小端字节序（Little Endian）：最高有效位存于最高内存地址，最低有效位存于最低内存处。

### 网络字节顺序NBO（Network Byte Order）  是  大端字节序
    
按从高到低的顺序存储，在网络上使用统一的网络字节顺序，可以避免兼容性问题。

如果两个主机储存方式不同，需要借助字节序转换函数 

#### 字节序转换函数
```c
include <arpa/inet.h>
//将主机字节序转换为网络字节序
 unit32_t htonl (unit32_t hostlong);
 unit16_t htons (unit16_t hostshort);
 //将网络字节序转换为主机字节序
 unit32_t ntohl (unit32_t netlong);
 unit16_t ntohs (unit16_t netshort);
```
函数（）内默认INADDR_ANY

### 用一下函数测试本机是大端还是小端

#include <stdio.h>
union
{
    char ch;
    int i;
}un;
int main(void)
{
    un.i = 0x12345678;
    if(un.ch == 0x12)
    {
        printf("big endian\n");
    }
    else
    {
        printf("small endain\n");
    }
    return 0;

### 主机字节顺序（HBO，Host Byte Order）  
   
发送数据按内存地址从低到高的顺序发送 

	
	
	