Unity通过此插件可用来开发跨平台应用。而且凉鞋有这方面的课程，而且不只一套。
# 版本要求：
①Unity version >= 2018.3
②.Net运行版本 = 4.0
![](https://i.loli.net/2019/09/22/lRNByYLMDTiF3KX.png)
③场景中必须有UGUI Canvas && EventSystem

单纯做App的话，场景中只需要Canvas && EventSystem

# 导入插件
项目地址：https://github.com/UnityTech/UIWidgets
在资源管理器中打开`Packages`目录，将`com.unity.uiwidgets`文件夹复制到这个目录下。
`com.unity.uiwidgets`是一层目录，其目录下是所有的文件和文件夹，不能再再套个`com.unity.uiwidgets`目录

![UIWidgets](https://i.loli.net/2019/09/22/PNAbMZGh31TdWXJ.png)

导入成功之后在Unity中显示的目录名为：`UIWidgets`

# 调试控制台
需要在PlayerSettings中的Other Settings → Scripting Define Symbols 中填入：`UIWidgets_DEBUG`
然后在Windows → Analysis → UIWidgets Inspector中就能打开调试控制台了。
![](https://i.loli.net/2019/09/26/AFvTNYsOlKyctog.png)