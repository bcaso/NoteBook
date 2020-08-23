---
title: ADO.NET
tags: Csharp, Sql
grammar_mindmap: true
renderNumberedHeading: true
grammar_code: true
grammar_mathjax: true
---

# 开发中要了解的
SqlHelper + App.config 

>SQLHelper类方法介绍及简单使用
https://blog.csdn.net/u013201439/article/details/51591324
https://www.cnblogs.com/heisehenbai/p/6852748.html

基础知识（连接及操作数据库）：https://zhuanlan.zhihu.com/p/68905542#%E5%B8%B8%E7%94%A8%E6%93%8D%E4%BD%9C

# 连接字符串
## MYSQL与MSSQL的两种格式
```csharp?linenums
            //Connect 2 mssql
			using (SqlConnection sqlConnection = new SqlConnection()) {
				Console.Clear();
				Console.WriteLine("Please input the password 4 mssql:");
				string pwd = Console.ReadLine();
				sqlConnection.ConnectionString = "Data Source=127.0.0.1;Initial Catalog=master;User ID=sa;Password=" + pwd; 
				sqlConnection.Open();
				Console.WriteLine("mssql connected successful");
				Thread.Sleep(2000);
				Console.WriteLine("mssql disconnected");
			}

			Thread.Sleep(2000);

			//Connect 2 mysql 
			using (MySqlConnection mySqlConnection = new MySqlConnection()) {
				Console.Clear();
				Console.WriteLine("Please input the password 4 mysql:");
				string pwd = Console.ReadLine();
				mySqlConnection.ConnectionString = "Data Source = 127.0.0.1;Initial Catalog =sys;User ID =root;Password = " + pwd;
				mySqlConnection.Open();
				Console.WriteLine("mysql connected successful");
				Thread.Sleep(2000);
				Console.WriteLine("mysql disconnected");
			}

			//区别在于mysql 没有 master数据库，默认的是sys；mysql也没有sa用户，默认的是root
		}
```
## 使用App.Config配置SQL连接的两种方式
### 第一种简单方式
MainFrm.cs
```c#
using System;
using System.Configuration;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace SqlDataAdapter适配器 {
	public partial class MainFrm : Form {
		public MainFrm() {
			InitializeComponent();
		}

		private void MainFrm_Load(object sender, EventArgs e) {
			//把UserInfo表中的数据加载到窗体的DataGridView
			using (SqlConnection sqlConnection = new SqlConnection()) {
//				sqlConnection.DataSource = "127.0.0.1"; //属性都是只读的，不能直接赋值
				string dataSource     = ConfigurationManager.AppSettings["DataSource"];
				string initialCatalog = ConfigurationManager.AppSettings["InitialCatalog"];
				string userID         = ConfigurationManager.AppSettings["UserID"];
				string password       = ConfigurationManager.AppSettings["Password"]; //测试时密码需要修改
				sqlConnection.ConnectionString = $"Data Source = {dataSource}; Initial Catalog = {initialCatalog}; User ID = {userID}; Password = {password};";

				sqlConnection.Open();

				MessageBox.Show("MSSQL Connected successful");
			}
		}
	}
}
```
AppConfig.xml
```xml
<?xml version="1.0" encoding="utf-8"?>

<configuration>
    <!--
    写法介绍
     https://gameinstitute.qq.com/community/detail/126519      
     appSettings似乎也是固定的。。。。
    -->
    <appSettings>
        <add key="DataSource" value="127.0.0.1"></add>
        <add key="InitialCatalog" value="master"></add>
        <add key="UserID" value="sa"></add>        
        <add key="Password" value="123456"></add>
    </appSettings>

    <startup>
        <supportedRuntime version="v4.0" sku=".NETFramework,Version=v4.6.1" />
    </startup>
</configuration>
```
### 第二种方式
MainFrm.cs
```csharp
...
    //获取连接字符串
    string connStr = ConfigurationManager.ConnectionStrings["sql"].ConnectionString;
...
```
AppConfig.xml
```xml
<?xml version="1.0" encoding="utf-8"?>

<configuration>
    <!--
     这个connectionStrings似乎也是固定的，格式大概都是一样的，标准格式,最后密码那个字段的分号可以省略
     这个没怎么看懂，来自sql与ado四天 
    -->
    <connectionStrings>
        <add name="sql" connectionString="Data Source=127.0.0.1;Initial Catalog=master;User ID=sa;Password=123456;" />
    </connectionStrings>
    <startup>
        <supportedRuntime version="v4.0" sku=".NETFramework,Version=v4.6.1" />
    </startup>
</configuration>
```
### 关于App.Config
```xml
<?xml version="1.0" encoding="utf-8" ?>
<configuration>
  <connectionStrings>
    <add name="conn" connectionString="this is connection string"/>
  </connectionStrings>
  <appSettings>
    <add key="key1" value="value1" />
    <add key="key2" value="value2" />
  </appSettings>
</configuration>
```
从这段代码可以看出，App.config完全是xml文档。它有如下几个特点。
1、它有一个`<configuration>`标签，所有的配置项都在`<configuration>`标签下面。
2、C#内置了一个`<connectionStrings>`节点，专门用于配置数据库连接字符串。它下面可以使用`<Add>`节点来添加多个数据库连接字符串。
3、`<appSettings>`，大家了解Web.config的应该很熟悉它，它可以配置任何`key-value`这样的键值对。最早没有<connectionStrings>的时候，我们也是把数据库连接的字符串放在`<appSettings>`里面的。

从这段代码可以看出，App.config完全是xml文档。它有如下几个特点。
1、它有一个<configuration>标签，所有的配置项都在<configuration>标签下面。
2、C#内置了一个<connectionStrings>节点，专门用于配置数据库连接字符串。它下面可以使用<Add>节点来添加多个数据库连接字符串。
3、<appSettings>，大家了解Web.config的应该很熟悉它，它可以配置任何key-value这样的键值对。最早没有<connectionStrings>的时候，我们也是把数据库连接的字符串放在<appSettings>里面的。

下面我们写一个程序来看看怎么从App.config这个程序配置文件中获取配置信息。

```c#?linenums
using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Configuration;

namespace AppConfig
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("ConnectionStrings:");
            // ConfigurationManager.ConnectionStrings是一个ConnectionStringSettingsCollection对象
            // 按数字循环得到一个个ConnectionStringSettings对象
            // 每个ConnectionStringSettings对象有Name和ConnectionString属性
            for (int i = 0; i < ConfigurationManager.ConnectionStrings.Count; i++)
            {
                string name = ConfigurationManager.ConnectionStrings[i].Name;
                string connectionString = ConfigurationManager.ConnectionStrings[i].ConnectionString;
                Console.WriteLine(i.ToString() + ". " + name + " = " + connectionString);
            }
            //也可以如下操作，使用ConnectionStringSettings类型来进行foreach遍历
            foreach (ConnectionStringSettings conn in ConfigurationManager.ConnectionStrings)
            {
                string name = conn.Name;
                string connectionString = conn.ConnectionString;
                Console.WriteLine(name + " = " + connectionString);
            }
            //直接获取conn的值
            Console.WriteLine("\r\nGet the value of the node named \"conn\":");
            Console.WriteLine(ConfigurationManager.ConnectionStrings["conn"].ConnectionString);
            Console.WriteLine("");

            Console.WriteLine("AppSettings:");
            //AppSettings是NameValueConnection类型，使用AllKeys返回一个所有Key组成的字符串数组
            string[] keys = ConfigurationManager.AppSettings.AllKeys;
            for (int i = 0; i < keys.Length; i++)
            {
                string key = keys[i];
                //通过Key来索引Value
                string value = ConfigurationManager.AppSettings[key];
                Console.WriteLine(i.ToString() + ". " + key + " = " + value);
            }
            // 没有NameValuePair这样的对象，所以无法使用foreach来进行循环

            //直接获取key1的值
            Console.WriteLine("\r\nGet the value of the key named \"key1\":");
            Console.WriteLine(ConfigurationManager.AppSettings["key1"]);

            //pause the process
            Console.ReadKey();
        }
    }
}
```
上面演示了如何遍历`<connectionStrings>`，如何遍历`<appSettings>`，如何单独获取某一个`connectionString`，如何单独获取某个`appSetting`。

App.config和Web.config的语法格式是完全一样的，只是一个用户WinForm程序，一个用于Web程序。

App.config在编译之后，将会被编译到bin\Debug目录下，文件名为“应用程序名.exe.config”。
  

>C#中App.config文件的使用：http://www.splaybow.com/post/csharp-app-config.html
使用操作包括修改保存 https://blog.csdn.net/e295166319/article/details/77839798
修改保存配置文件 https://blog.csdn.net/wzk456/article/details/49001391

# 连接池
默认最小是4个

只要两个连接字符串不相当，那么在连接池中这就是两个连接。

连接对象只可以被open()一次，在close()后可以再进行open()操作。但是Dispose()后这个连接就会被释放，之后就不能再被打开了。

# sql注入漏洞
一般在登录的场景下：使用一些特殊的字符进行对数据库进行攻击
' or 2 = 2; --

解决方式：
sql参数化：SqlParameter

## DataSet 和 DataTable
两个Csharp类
DataSet 是表的集合
DataTable 是列和行的集合

```c#?linenums
//把UserInfo表中的数据加载到窗体的DataGridView
using (SqlConnection sqlConnection = new SqlConnection()) {
	...
	//连接字符串
	sqlConnection.ConnectionString = "Data Source = .; Initial Catalog = StudentDB; User ID = sa; Password = 123456;";				
	//查询命令
	string strSql = @"SELECT TOP (1000) [StuInfoID], [StuName],[StuAge] FROM [StudentDB].[dbo].[StudentInfo]";
	//创建一个适配器类
    using (SqlDataAdapter adapter = new SqlDataAdapter(selectCommandText: strSql, selectConnection: sqlConnection) ) {
	    //adapter: 一个连接，cmd.CommandText(Sql)
	    DataTable dataTable = new DataTable();
	    //把数据库中的数据填充到内存表dataTable中
	    //填充之前不需要打开数据库连接，Adapter会自动打开连接
	    adapter.Fill(dataTable);
	    //在DataGridView控件上显示结果
	    this.dgvUserInfo.DataSource = dataTable;
	}
}
```

## SqlDataAdapter数据访问适配器 与 SqlDataReader
SqlServer 表 → 适配表（SqlDataAdapter） → DataSet、DataTable
建立连接后，SqlDataAdapter将所有数据加载到内存后，然后连接就关闭了

而SqlDataReader，在建立连接后，一直保持连接状态，数据都在数据库中，只有用到哪个数据才会取哪个

## 修改并保存
WinForm 下使用 DataGridView控件
注意：
&emsp;最好把从数据库读取的数据表，序列化为一个强类型的类，然后从DataGridView做修改，保存到类，类再update到数据库
使用及操作案例：
https://www.cnblogs.com/herbert/archive/2010/08/31/1813824.html
