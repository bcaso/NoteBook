# 数据库概念
数据库就是数据仓库
DBMS 数据库管理系统。SQLServer Oracle
## 实例名
用来区分安装在同一台计算机上不同的MSSqlServer服务。

# 数据库基本组成
一个数据库可以有多个架构，一个架构可以有多个表
## 数据库
### 架构（表的分组）
#### 表
列（Column字段，类型，长度，约束等）
行（Row）
主键
外键


# 连接数据库
打开Microsoft SQL Server Management Studio

会弹出下面的对话框
![enter description here](https://i.loli.net/2019/05/20/5ce26c6f2e26339607.jpg)

如果不小心点了关闭，那么就点击下图中的红圈部分重新打开对话框：
![enter description here](https://i.loli.net/2019/05/20/5ce26c57982b167515.jpg)

Server name:
本地数据库（.代表本地数据库,(local) 也代表本地数据库，或者机器名God）
回环地址：127.0.0.1
![机器名为God](https://i.loli.net/2019/05/20/5ce26cc58242176604.jpg)

后面再加实例名

实例名的查看
打开服务
命令`services.msc`
或者任务管理器的Services选项卡的 最下面的 `Open Services`
![](https://i.loli.net/2019/05/20/5ce26eb7945a288713.jpg)
可以使用Listary快速定位，与Explorer一样，中间的空间用的都是ListView，所以支持快速定位，包括中文，默认支持，即使没有Listary软件
找到`SQL Server(*)`
()里面的就是实例名。

![括号中的实例名为SQLEXPRESS](https://i.loli.net/2019/05/20/5ce26fb7e23f853438.jpg)

如果实例名是`MSSQLSERVER`那么就不需要加上实例名。这个是默认实例名。

并确保该服务`SQL Server(*)`正在运行，否则后续是连接不上的。

Authentication:
验证方式，开发中不可能用Windows Authentication.
开发时都用ip地址


或者服务器地址

或者局域网IP地址


sa用户的权限最大，全拼System Administator

网络及端口状态查询：
`netstat -a -n` -a == all, -n == number
## tcp协议开启
![](https://i.loli.net/2019/05/20/5ce2988f2787975394.jpg)
之后就可以在局域网内通过ip地址访问数据库了。ip地址是局域网中数据库所在的电脑的ip
可能遇到 Cannot connect to WMI provider. You do not have permission or the server is unreachable
的问题，解决步骤见下面<a href = "#Question2" title = "可能遇到的问题">点击跳转到解决步骤</a>
把服务器的TCP/IP和客户端的TCP/IP都开启，找全部的TCP/IP，都开启就没错
# 数据库文件默认位置
`C:\Program Files\Microsoft SQL Server\MSSQL14.SQLEXPRESS\MSSQL\DATA\`

# 命名规范
## 表名 -> 类名
表名就是类名。命名规范同类名
## 列名 -> 属性名


# 数据类型
## n开头 2个字节一个字符
NChar, NvarChar(32) N:Unicode(特殊情况下4个字节表示一个字符)
为防止乱码,nvarchar已经成为了一个标准。
## varchar(32) 一个字节一个字符
## 分类
### 二进制数据类型
存储非字符和文本的数据
#### Image
用来存放图像
实际根本不会这么去用，图片一般都是存放在文件中，把路径放出来。存放在数据库中，性能很低。
#### 文本数据类型
字符数据包括任意字母，符号和数字字符的组合
##### char，8000
8000字节,磁盘的一个页，多余8000就跨页，跨页性能差，磁盘一次读一页
固定长度的非Unicode字符数据。固定长度的字符串相对于可变长度的字符串来说效率要高一些，在数据长度固定的情况下优先选用固定长度，省去了计算长度的过程，提高效率。
##### varchar，8000
可变非Unicode数据
##### nchar, 4000
固定长度的 Unicode 数据
##### nvarchar, 4000
可变长度的Unicode数据
##### Text， varchar(max)
存储长文本信息（指针，2G）
varchar(max)，大字符串类型可以保存
##### Ntext, nvarchar(max)
nvarchar(max)代替

#### 日期和时间
日期和时间在单引号内输入
##### Datetime
必须选择可以为null,最早能表示1753
##### datetime2
必须可以为null,可以存储更早日期
#### 数字数据
该数据仅包含数字，包括正数、负数以及分数
##### int, smallint 整数
##### float，real
数字decimal
##### bit
只能 0 | 1，显示的是True(1)或false(0)
##### uniqueidentifier
全球唯一标志


# 主键
两种类型，自动增长的和GUID
主键与其他列数据不能重复。且不能为空
## 自动增长
从标志种子开始增加标识增量的数
## GUID
```sql?linenums
--创建一个guid
select NEWID()
```

# 数据库的迁移方案
## 分离 附加
*.mdf main database file 主数据库文件
*.ldf log database file 数据库日志文件

### 可能出现的问题
#### 权限问题
启动Adminstrator账号
把数据库文件放到默认的数据库文件存放目录。
#### 数据库文件兼容级别
## 脱机 附加，联机

## 备份 还原

# 可能遇到的问题
## 阻止保存要求重新创建表的更改
工具 → 选项 → 设计器 → 取消打钩“阻止保存要求重新创建表的更改”
![Prevent saving changes that require table re-creation](https://i.loli.net/2019/05/20/5ce27a8b4b01832029.jpg)

<a href = "#" name = "Question2"></a>
## Cannot connect to WMI provider. You do not have permission or the server is unreachable
https://support.microsoft.com/ar-sa/help/956013/error-message-when-you-open-sql-server-configuration-manager-in-sql-se
修复命令：`mofcomp "%programfiles(x86)%\Microsoft SQL Server\number\Shared\sqlmgmproviderxpsp2up.mof"`
其中的number是具体数字，当前版本是2017，我看文件夹中最大的数字是140，就用140替换了。
![140](https://i.loli.net/2019/05/20/5ce296c1b605e43722.jpg)

显示结果：
![](https://i.loli.net/2019/05/20/5ce296fb6e49982129.jpg)

然后Computer Management右边的数据库管理项就能查看了
![](https://i.loli.net/2019/05/20/5ce297568e31995862.jpg)

这个的打开步骤：找到`This PC` → 右键 → 管理
## A newvork-related or instance-specific error occurred while establishing a connection to SQL Server. 
The server was not found or was not accessible. Verify that the instance name is correct and that 
SQL Server is configured to allow remote connections. (provider: Named Pipes Provider, error: 40 • 
Could not open a connection to SQL Server) (Microsoft SQL Server, Error: 2) 
The system cannot find the file specified

解决步骤：
把TCP/ip开启，然后重启 SQL Server服务
或者在IPAddress选项卡中把其中一IP地址设置为当前电脑的ipv4地址（局域网）,enabled 端口为1433，保存后再restart Sql Server.
https://www.cnblogs.com/FlyGoldfish/articles/6995063.html
