## service
    服务程序采用Java语言，以Spring Boot整合SSM框架，利用其自动配置、Mapper映射及注解开发，减少代码量及调试难度。
### 一、	程序目录结构
1.	实体类（com.springboot.domin）: Book.java、Record.java
2.	Mapper（com.springboot.myMapper）
3.	Controller（com.springboot.Controller）: MybatisController.java
4.	MyspringbootApplication 
5.	Application.properties（resources）
### 二、	提供的服务（注释为路由、请求方法及请求Body的格式）
1.	根据客户端发来的书名查询书籍信息（POST、/select、{ “ name ” : ” ” } ）。
2.	检查当前视觉识别的书籍是否存在异常并更新实时位置，根据与标准位置的比较设置标志位Error，若异常为1。（POST、/update、{ “identity”：“”，“shelf ：“”，“row”：“”，“col”：“” ”}）。
3.	提供借书和还书操作的接口，判断操作过后设置标志位stat，借书则在馆标志stat为1，反之为0，同时并记录借书人保存在“stuId”。（POST、/borrow、{“identity”：“”，“stuId”：“”，stat：“”}）。
4.	一键获取借出书籍列表（GET、/outRecords、发送请求即可，无需Body）
5.	一键获取错位乱架书籍：根据服务2设置的error检索出所有异常书籍（GET、/selectErrorBooks、发送请求即可，无需Body）
