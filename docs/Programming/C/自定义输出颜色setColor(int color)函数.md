---
title: 自定义输出颜色setColor(int color);函数
tags: C,Function
grammar_cjkRuby: true
---
```c?linenums
#include <stdio.h>
#include <Windows.h>
void setColor(int color);

int main(void){
    setColor(2);        //绿色
    printf("Hello World!");//控制台以绿色字体输出
    return 0;
}
//自定义的文字颜色函数   
void setColor(int color){
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
```
`WORD`在`windows.h`中定义，等同于`unsigned short`，使用低4位表示文字（前景）颜色，高4位表示文字背景颜色，所以它的取值为xx。x为一位16进制数，即0~F都可以使用，可以随意组合。

>关于高4位，低4位以及其他**位 https://blog.csdn.net/MyUserAndWuBin/article/details/45844283



0~F 分别代表的颜色如下：
```
0 = 黑色    8 = 灰色    1 = 淡蓝      9 = 蓝色
2 = 淡绿    A = 绿色    3 = 湖蓝      B = 淡浅绿  
C = 红色    4 = 淡红    5 = 紫色      D = 淡紫  
6 = 黄色    E = 淡黄    7 = 白色      F = 亮白
```
>原文地址: http://c.biancheng.net/cpp/html/2939.html