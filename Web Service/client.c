#include<unistd.h>
#incldue<netdb.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <arpa/inet.h

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		printf("usage: %s IP port \n", argv[0]);
		exit(1);
	}
	
	int sockfd = socket(AF_INET , SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket error");
		exit(1);
	}
	
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&serveraddr.sin_addr.s_addr);
	
	if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
	{
		perror("connect error");
		exit(1);
	}
	
	char buf[1024];
	memset(buf,0,sizeof(buf));
	size_t size;
	if(size = read(sockfd,buf,sizeof(buf))<0)
	{
		perror("read error");
		exit(1);
	}
	if(write(STDOUT_FILENO,buf,size) != size)
	{
		perror("write error");
		exit(1);
	}
	
	close(sockfd);
	return 0;
	
	
}