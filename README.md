# Qt_Mysql_practice
experience sharing

qt学习，在借鉴网上一些方案后，用纯代码的方式实现布局

基于qt5和Mysql实现的库存管理数据库

开发环境：

- Qt 5.14.2
- VisualStudio 2022
- Mysql 8.0.22

### 运行前所需配置：

1.增加stockdatabase数据库,运行SQL文件（字符集选utf-8排序规则为utf8_general_ci)(不知道 其他的会不会出现中文乱码，做这个的时候因为乱码弄了好一会)QWQ

2.在ODBC数据源中进行设置

 ![]([https://github.com/QWSFAY/Qt_Mysql_practice/blob/main/img/1.png?raw=true)

![](https://github.com/QWSFAY/Qt_Mysql_practice/blob/main/img/2.png?raw=true)

![](https://github.com/QWSFAY/Qt_Mysql_practice/blob/main/img/3.png?raw=true)

![](https://github.com/QWSFAY/Qt_Mysql_practice/blob/main/img/4.png?raw=true)

最后这Character Set选gbk很重要,不然之后运行可能会出现中文乱码。Database没东西可能是你的User 或者 Password输错了.

3.点击StockManagementSystem.sln 在MainWidget.cpp中更改你的数据库密码

4,运行

### 运行效果图

![](https://github.com/QWSFAY/Qt_Mysql_practice/blob/main/img/5.png?raw=true)

![](https://github.com/QWSFAY/Qt_Mysql_practice/blob/main/img/6.png?raw=true)

![](https://github.com/QWSFAY/Qt_Mysql_practice/blob/main/img/7.png?raw=true)
