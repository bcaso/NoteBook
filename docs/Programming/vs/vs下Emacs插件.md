---
title: vs下Emacs插件
tags: IDE
grammar_cjkRuby: true
---
插件下载地址：https://marketplace.visualstudio.com/items?itemName=JustinClareburtMSFT.EmacsEmulation

# 部分快捷键：
代码注释是`c-i,c-c`,取消注释是`c-i,c-u`
代码提示是`m-/`

原有代码对齐`Edit.FormatDocument`,快捷键是`c-k,c-d`,这个在使用emacs插件的情况下未定义（vs2017）
Emacs中对齐选中代码的快捷键`m-f8`,但是代码对齐的快捷键没有定义，需要自定义

![emacs下代码格式化快捷键](https://i.loli.net/2018/11/19/5bf2269e9c64d.jpg)
2018年11月19日补充，代码格式化在emacs插件下已定义。快捷键为`F1`;如上图
![快捷键](https://i.loli.net/2018/11/19/5bf22877a2735.jpg)
> `F1`代码格式化
`Alt + \` 删除当前行下的空白符（空格）
`Shift + Alt + =`展开所选
`Shift + Alt + -`折叠所选
`Ctrl + I, Ctrl + C`注释所选代码
`Ctrl + I, Ctrl + U`取消对所选代码的注释

其他快捷键的寻找方式，在下图中找到vs2005中快捷键。
https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf
及对应的英文解释
然后在vs中`Tools → Options → keyboard`反搜索英文解释就可找到对应的快捷键。

# vs原快捷键
`Ctrl + k + d`: 快速对齐代码
`ctrl + j　　`: 快速弹出智能提示
`shif + end、shift + home`
`ctrl + k + c`: 注释所选代码
`ctrl + k + u`: 取消对所选代码的注释
`f1　　　　　`: 转到帮助文档
`Alt + shift + f10` 找到包含此类的头文件