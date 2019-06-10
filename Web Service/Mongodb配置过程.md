# Mongodb 

在Linux上Mongodb的安装、配置

## Mongodb 安装
```c
curl -O https://fastdl.mongodb.org/linux/mongodb-linux-x86_64-3.0.6.tgz    # 下载

tar -zxvf mongodb-linux-x86_64-3.0.6.tgz  
	
```
## Mongodb 配置

### 在/usr/local/mongodb 中创建配置文件压存放 data、log、和conf文件（log不应为目录，应该是.log文件）
	
### 配置文件mongodb.conf
```c
vim mongdb.conf
		
dbpath=/data文件的路径/
		
logpath=/mongodb.log的路径/
		
port=27017
		
fork=true
		
journal=false
		
authen = true   //mongodb的user可以靠authen.xxx登陆
		
```

### 配置环境变量
```c
在Linux系统根目录下的/etc/profile 添加 export PATH=$PATH:/mongodb 的bin目录路径/
    
执行 source /etc/profile
	
将mongo路径软链到/usr/bin路径下，方便随处执行mongo命令
执行  ln -s /bin目录下mongo的路径/  /usr/bin/mongo
	
这样便能在任意目录下 通过命令 “mongo” 来启动mongodb
```
	
	
	