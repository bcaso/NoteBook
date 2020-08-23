---
title: Unity中的持久化数据PlayerPrefs
tags: Unity,PlayerPrefs
grammar_cjkRuby: true
---
# 1.Unity里提供了一种本地化存储的方式，能够简单的存一些比较小的数据。
这个方法写在Unity的PlayerPrefs类中。

根据API的介绍，可以理解为持久化储存，还可以理解为游戏存档， 玩RPG游戏的时候肯定会有游戏存档 存档中就会记录玩家以前游戏的过程，

这些都是以数据的形式存在PlayerPrefs中的。

一般情况下我们只能存储Int float 和String类型的数据
```cs
	void Start () {
        PlayerPrefs.SetInt("speed", 1);
        PlayerPrefs.SetFloat("Age",1.0f);
        PlayerPrefs.SetString("Name", "test");
	}
```
<br>
 第一个参数为存储时的名字，第二个参数是存储的具体值。

 当我们需要读取数据时也可以直接通过函数名取值
```cs
 PlayerPrefs.GetFloat("speed");
```
 有一种重写的方法，当两个参数时，如果取不到值，会返回后面的参数的值。
 // 这句还尚不知道是什么意思
 
 # 2.PlayerPrefs到底存储到了什么位置？
 以Windows为例，先看API中的介绍

在Windows独立模式下，PlayerPrefs被存储在注册表的 HKEY_CURRENT_USER\Software\[company name]\[product name]键下，这里company和product名是在Project Setting中设置的.

按照API的路径找了一下，发现有些问题。

首先，HKCU就是Windows中的注册表，首先通过Win+R 进入运行界面，输入regedit进入注册表
![](http://p75k5ihmt.bkt.clouddn.com/18-5-16/54159587.jpg)
还有个位置存放了这些东西,还不明白这两个地址分别代表着什么.
![](http://p75k5ihmt.bkt.clouddn.com/18-5-16/88211991.jpg)
我们存储的数据就在这里。这里company和product名我们可以在Unity中找到
![](http://p75k5ihmt.bkt.clouddn.com/18-5-16/78634303.jpg)
!具体图片[](http://p75k5ihmt.bkt.clouddn.com/18-5-16/55037895.jpg)


# 3.PlayerPrefs中的所有方法
```
DeleteAll   Removes all keys and values from the preferences. Use with caution.
从游戏存档中删除所有key。请谨慎使用。
DeleteKey   Removes key and its corresponding value from the preferences.
从游戏存档中删除key和它对应的值。
GetFloat    Returns the value corresponding to key in the preference file if it exists.
如果存在，返回游戏存档文件中key对应的浮点数值。
GetInt  Returns the value corresponding to key in the preference file if it exists.
如果存在，返回游戏存档文件中key对应的整数值。
GetString   Returns the value corresponding to key in the preference file if it exists.
如果存在，返回游戏存档文件中key对应的字符串值。
HasKey  Returns true if key exists in the preferences.
如果key在游戏存档中存在，返回true。
Save    Writes all modified preferences to disk.
写入所有修改参数到硬盘。
SetFloat    Sets the value of the preference identified by key.
设置由key确定的浮点数值。
SetInt  Sets the value of the preference identified by key.
设置由key键确定的整数值。
SetString   Sets the value of the preference identified by key.
设置由key确定的字符串值。
```