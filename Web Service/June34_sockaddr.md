## Linux TCP通信基础——sockaddr结构体
   
sockaddr  和  sockaddr_in 的介绍和区别

###sockaddr结构体
```c
struct sockaddr 
	{  
	 unsigned short sa_family;
	 char sa_data[14];                  
	};  
 	sa_family是通信类型，最常用的值是 "AF_INET"
	sa_data14字节，包含套接字中的目标地址和端口信息
	但是sockaddr把目标地址和端口混在一起  所以用  sockaddr_in  (in代表internet
```

###sockaddr_in结构体
```c
struct sockaddr_in 
	{ 
		short int sin_family;
		unsigned short int sin_port; 
		struct in_addr sin_addr;
		struct in_addr 
		{ 
    		unsigned long s_addr;
     	}
                
			unsigned char sin_zero[8];
	}   
```

*sockaddr_in结构体元素*
sin_family   地址族，常用AF_INET
sin_port     16位TCP端口号
sin_addr     32位IP地址
