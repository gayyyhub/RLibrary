##MongoDB的基本操作
先在MongoDB shell下通过 mongo命令 登陆到数据库

### 查看数据库、集合、用户信息、切换等
```c
show dbs;                  #查看全部数据库

show collections;          #显示当前数据库中的集合（类似关系数据库中的表）

show users;                #查看当前数据库的用户信息

use <db name>;             #切换数据库跟mysql一样

db;或者db.getName();        #查看当前所在数据库

db.help();                 #显示数据库操作命令，里面有很多的命令 
db.foo.help();             #显示集合操作命令，同样有很多的命令，foo指的是当前数据库下，一个叫foo的集合，并非真正意义上的命令 
db.foo.find();             #对于当前数据库中的foo集合进行数据查找（由于没有条件，会列出所有数据） 
db.foo.find( { a : 1 } );  #对于当前数据库中的foo集合进行查找，条件是数据中有一个属性叫a，且a的值为1
```

### 创建一个Test数据库例子
```c
> use test;             #创建数据库
switched to db test
> db;               
test
> show dbs;           #检查数据库
admin 0.000GB
local 0.000GB

> db.test.insert({"_id":"520","name":"xiaoming"})         #创建表

WriteResult({ "nInserted" : 1 })

> db.createUser({user:"xiaoming",pwd:"123456",roles:[{role:"userAdmin",db:"test"}]})        #创建用户
Successfully added user: {
"user" : "xiaoming",
"roles" : [
{
"role" : "userAdmin",
"db" : "test"
}
]
}
db.removeUser("userName");         #删除用户
show users;                        #显示当前所有用户
```

### 删除当前使用数据库
```c
> show dbs;
admin 0.000GB
local 0.000GB
test 0.000GB
test_1 0.000GB

> db;
test_1

> db.dropDatabase();
{ "dropped" : "test_1", "ok" : 1 }


> show dbs;
admin 0.000GB
local 0.000GB
test 0.000GB
```
 
### 显示当前db状态  db.stats();
```c
> db.stats();
{
    "db" : "test_1",
    "collections" : 0,
    "views" : 0,
    "objects" : 0,
    "avgObjSize" : 0,
    "dataSize" : 0,
    "storageSize" : 0,
    "numExtents" : 0,
    "indexes" : 0,
    "indexSize" : 0,
    "fileSize" : 0,
    "ok" : 1
}
```
 
### mongodb find查询文档
```c
基本语法：

db.表名.find({'key':'value'});

实例：

> show dbs;
admin 0.000GB
easy-mock 0.001GB
local 0.000GB
> use easy-mock
switched to db easy-mock
> db
easy-mock
> show collections;
groups
mock_counts
mocks
projects
user_group
user_project
users
> db.users.find({'name':'xiaoming'});
{ "_id" : ObjectId("5bc859307e81d95b15f67c5c"), "head_img" : "//img.souche.com/20161230/png/fd9f8aecab317e177655049a49b64d02.png", "nick_name" : "1539856688465", "password" : "$2a$08$7mAecPo6N8ATesAxfKrPG.wb10Ns.LfntUNkce7p2pAJ0kAvW3fPm", "name" : "xiaoming", "create_at" : ISODate("2018-10-18T09:58:08.465Z"), "__v" : 0 }
```

### 修改文档  mongodb updata
```c
# 查找name为xiaoming的用户，将用户的密码更改

> db.users.update({'name':'xiaoming'},{$set:{'password':'$2a$08$UIEXZ7uK1opggCsTkmE2buE.EuWjchH42GYDnPcEn0PL/Y5dVT7l2'}})

> db.users.find({'name':'xiaoming'});
{ "_id" : ObjectId("5bc859307e81d95b15f67c5c"), "head_img" : "//img.souche.com/20161230/png/fd9f8aecab317e177655049a49b64d02.png", "nick_name" : "1539856688465", "password" : "$2a$08$UIEXZ7uK1opggCsTkmE2buE.EuWjchH42GYDnPcEn0PL/Y5dVT7l2", "name" : "xiaoming", "create_at" : ISODate("2018-10-18T09:58:08.465Z"), "__v" : 0 }
```