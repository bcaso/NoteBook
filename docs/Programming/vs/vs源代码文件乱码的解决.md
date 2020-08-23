---
title: vs源代码文件乱码的解决
tags: IDE
grammar_cjkRuby: true
---
最近在写c程序的时候，遇到了这个问题由于关机时没有关闭vs，导致电脑重启后打开之前的代码，关于中文的部分都是乱码。
# 解决方法：
[![点我链接到知乎的相关问题页](https://i.loli.net/2018/11/19/5bf22decd1214.gif)](https://www.zhihu.com/question/37252051)
`c-x,c-w` → `Save with Encoding` → Encoding选择 `UTF-8 650001`  → `OK`

# 问题
用这个方法会造成代码无法编译。
另外我发现，即使是从别处粘贴到vs中的代码也有可能出现无法编译的情况。

![cannot read compiler command line
](https://i.loli.net/2018/11/22/5bf63888989b8.jpg)