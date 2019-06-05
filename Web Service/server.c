#include<stdio.h>
#include<sys/socket.h>   //2是listen()和socklen_t数据类型的头文件
#include<sys/types.h>   //2,3是socket(),bind()的头文件
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>  //6是socklen_t数据类型的头文件

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("usage:%s #port\n", argv[0]);
		exit(1);
	}
	if(signal(SIGINT, sig_handler) == SIG_ERR)  //设置某一信号的对应动作
	{        //type     //action
		perror("signalsigint error");
		exit(1);
	}
	
	//创建socket
	int sockfd;
	if(sockfd=(AF_INET,SOCK_STREAM,0)== -1)
	{
		perror("socket error");
		exit(1);
	}
	
	//把socket和地址（ip,port）进行绑定
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	//origin: void *memset(void *buffer, int c, int count)
	//buffer是指针或数组 c：赋给buffer的值 count：buffer的长度
	//此函数在socket中多用于清空数组，对一段内存空间全部设置为某个字符。
	serveraddr.sin_family = AF_INET;   //AF_INET说明要用TCP协议
	serveraddr.sin_port = htons(atoi(argv[1])); //转换为网络字节序
	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);  //响应所有的网卡请求
	
	if(bind(sockfd,(struct sockaddr*)(&serveraddr),sizeof(serveraddr)) < 0 )
	{//绑定成功返回0 否则返回-1
     //sockfd是要绑定的服务器套接字
	 //第二个参数是服务器的地址信息（协议组，IP，PORT）
	 //第三个参数是服务器的地址信息长度
		perror("bind error");
		exit(1);
	}
	
	if(listen(sockfd,10)<0)
	{//listen()使 “主动连接“套接口 变为 “被连接”套接口
     //使一个进程可以接受其他进程的请求，从而成为一个服务器进程
	 //在TCP中把进程变成一个服务器，并指定相应的套接字变为  被动连接
	 //一般在调用bind（）后   调用accept（）之前
	 
	 //第一个参数指定sockfd为被动套接口
	 //第二个参数指定最大连接数   一般小于30
		
	 //函数成功返回0  否则返回-1
	 
	 perror("listen error");
	 exit(1);
	}
	
	struct sockaddr_in clientaddr;
	socklen_t clientaddr_len = sizeof(clientaddr);   //Linux平台下socklen_t定义在unistd.h和sys/socket.h
	while(1)
	{
		int fd = accept(sockfd, (struct sockaddr*)&clientaddr, &clientaddr_len);
		//原理同bind
		if (fd < 0)  
		{
			perror("accept error");
			continue;
		}
		
		//调用IO函数和连接的客户端进行双向通信
		out_addr(&clientaddr);
		do_service(fd);
		
		//关闭socket
		close(fd);
	}
	
	return 0;
	
}