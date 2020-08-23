[TOC]

# Hello World
安装两个软件：
①Visual Studio Code
②.Net Core SDK(just the sdk)
③C# （在扩展中搜索C#并安装）

ctrl + tilde(波浪线，ESC键的下面) 跳转到terminal(命令行)
然后输入命令：
```console
mkdir ./HelloWorld	//或者 mkdir "./CSharp/HelloWorld"   有双引号，这将创建两级目录
cd ./HelloWorld		//或者 cd ./CSharp/HelloWorld
dotnet new console	//创建一个控制台程序
```
>C#7.0 本质论（page3）

这样一个HelloWorld就建好了，在左边能看到项目文件。
![](https://i.loli.net/2019/11/22/XCcyrAI36fsp5ab.png)



## 运行
![](https://i.loli.net/2019/11/22/rS72amoINEQR4yJ.png)
解释：
①打开Program.cs(包含Main方法的类)
②按`F5`，报错不管，继续按F5，然后就会添加`launch.json`, `tasks.json`到项目中，然后再按F5就能运行了。

选择运行环境`.NET Core`
③
报错：
![](https://i.loli.net/2019/11/22/zCvRN25UmHArcuO.png)
再按下F5即显示选择运行环境的对话框

再点击F5,会跳转到
![](https://i.loli.net/2019/11/22/xbdszoVC1GchE2H.png)
同样是报错。
不必理会，继续点击F5即可。

点击VSCode的run按钮时会显示另一个错误：
![](https://i.loli.net/2019/11/22/cPUODlfpauiZTEn.png)
```console
[Running] scriptcs "c:\Users\god\source\EssentialCSharp\HelloWorld\Program.cs"
'scriptcs' is not recognized as an internal or external command, operable program or batch file.
```

`dotnet restore`重建项目，rebuild 项目，当项目有更改时，可重建。

>完整视频演示：
https://www.youtube.com/watch?v=t4heVCEe3u8
视频中使用的命令`dotnet new`在.net core 3.0或以上的版本中应该替换为`dotnet new console`



# 快捷键
`ctrl + ~` 打开命令行，是powershell模式,  （~ 英文是tilde [ˈtɪldə]）
`ctlr + p` 切换tab页，文件夹中的其他文件将都显示在这里。似乎比`ctrl + tab`要好用些。
`alt + 鼠标左键` 标记多个光标，这样可以同时编辑，esc退出编辑
`f1` | `ctrl + shift + p`显示Command palette（命令调色板 [ˈpælət] ）
`alt + shift + f` format document 格式化
`ctrl + E/R/P/Q`都是切换视图

# User settings && Workspace settings
User settings针对于当前电脑的每一个项目。
Workspace settings 针对于当前项目，重写User settings并应用到当前项目，其他项目看不到这个项目的设置，每个项目都有自己单独的Workspace settings，是个json文件，默认为空，使用的是User settings.

这个似乎跟Rider是一样的。

# 插件
代码格式化
1. C# FixFormat

单词拼写检查
1. Code Spell Checker

Git
1.  GitLens,团队开发必备，这个代码是谁修改的，谁写的，什么时候写的
2.  gitignore 右键忽略
3.  GitHistory 视觉化Commit图像
4.  gitflow 图形化版控流程
5. git-autoconfig 当有多个git账号时可能有需要


# Git
>https://www.youtube.com/watch?v=Fk12ELJ9Bww
非常详细

1. How to add an existing vs code project to git and github
2. How to do commit and push whenever changes happen
3. How to clone from github to vscode
4. How to remove project from git

Step 1 : Install git on your system

Step 2 : Create account on github - https://github.com/

Step 3 : Create a repository on github & copy url

Step 4 : Goto VS Code and open project/folder

note : check git is enabled from settings

Step 5 : Goto source control section & click on git icon

Step 6 : Give commit message & Commit the changes

Step 7 : Add remote repo (github repo)

Step 8 : Push commited changes to github repo

Step 9 : Check changes on github repo

![](https://i.loli.net/2019/11/22/S5atiBDOmxPGVHl.png)
不要勾选`Initialize this repository with a README`
这将使你立刻克隆Repository到你的电脑上，跳过并不勾选此项，则从一个已存在的Repository导入到这里。

问题的解决：
https://www.youtube.com/watch?v=wK1A2mNrZ9c

## azure
项目地址：
![](https://docs.microsoft.com/en-us/azure/devops/repos/git/_img/gitquickstart-vs2017/clone-url.png?view=azure-devops)
