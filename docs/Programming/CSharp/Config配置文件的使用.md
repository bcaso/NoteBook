>How to Use System.Configuration.ConfigurationManager on .NET CORE？
https://www.itnota.com/use-system-configuration-configurationmanager-dot-net-core/

使用NuGet搜索`System.Configuration.ConfigurationManager`并添加到项目中。

# 示例
App.config
```xml
	<appSettings>
    <add key="Db" value="server=(local);uid=sa;pwd=123;database=demo"/>
	</appSettings>
```
使用
```c#
public class DBHelper{
	static SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationSettings.AppSettings["Db"]);
	...
}
```

https://blog.csdn.net/e295166319/article/details/77839798

https://www.jianshu.com/p/3ef2af57a7f4

https://codeday.me/bug/20170704/33730.html