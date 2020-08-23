---
title: 自定义光标位置函数setCursorPosition(int x, int y);
tags: C,Function
grammar_cjkRuby: true
---
# 介绍
光标定位需要使用 `windows.h` 头文件中的`SetConsoleCursorPosition`函数，它的使用方式为：
`SetConsoleCursorPosition(HANDLE hConsoleOutput, COORD  dwCursorPosition);`
`hConsoleOutput`表示控制台缓冲区句柄，可通过`GetStdHandle(STD_OUTPUT_HANDLE)`来获得；`dwCursorPosition`是光标位置，也就是第几行第几列，它是 `COORD` 类型的结构体。
# 示例：
将光标定位到控制台的第3行第3列：
```c?linenums
//定义光标位置
COORD coord;
coord.X = 3;  //第3行
coord.Y = 3;  //第3列
//获取控制台缓冲区句柄，固定写法
HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//设置光标位置，固定写法
SetConsoleCursorPosition(ConsoleHandle, coord);
```
```c?linenums
#include <stdio.h>
#include <windows.h>
int main(){
    //定义光标位置
    COORD coord;
    coord.X = 3;  //第3行
    coord.Y = 3;  //第3列
    //获取控制台缓冲区句柄
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置光标位置
    SetConsoleCursorPosition(ConsoleHandle, coord);
   
    printf("123");//程序将从3,3的位置打印"123"
    return 0;
}
```
运行结果：
![](http://p2.i.img9.top/ipfs/Qmc2LFkLTkh2nXF5JtnREcG8oYUQXMn4cMdMTrYq95NyiK?2.png
)
>注意：窗口的左上角是第 0 行第 0 列，而不是我们通常所认为的第 1 行第 1 列。编程语言中的很多计数都是从 0 开始的，而不是从 1 开始。

# 自定义函数
```c?linenums
#include <stdio.h>
#include <windows.h>
//设置光标位置
void setCursorPosition(int x, int y);

int main(){
    setCursorPosition(3, 3);
    puts("★");
    setCursorPosition(1, 1);
    puts("◆");
    setCursorPosition(6, 6);
    puts("■");
    return 0;
}
//自定义的光标定位函数
void setCursorPosition(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
```
运行效果：
![](https://p0.cdn.img9.top/ipfs/QmWmha2xvKRMuJHJ7ecHwWgRGggPdN78artujeVnKPUbQa?0.png
)
在使用setCursorPosition函数前还可以使用setColor（自定义函数）来控制文字颜色。