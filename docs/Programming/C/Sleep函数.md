---
title: Sleep函数
tags: C,Function
grammar_cjkRuby: true
---
代码一：
```c?linenums
#include<stdio.h>
#include<Windows.h>

int main(void){
    printf("C语言中文网");
    Sleep(5000);    //程序暂停5秒钟
    return 0;
}
```
代码二：
```c?linenums
#include<stdio.h>
#include<unistd.h>

int main(void){
    printf("C语言中文网");
    sleep(5);   //程序暂停5秒钟
    return 0;
}
```

>综上所述，
`sleep(int seconds)`来自`Windows.h`，这个是Windows提供的接口，仅在Windows下使用。
`Sleep(int milliseconds)`来自`unistd.h`, 在Linux平台上也能用。


代码片段来自 {C语言中文网}(Xi Yu Yan Zhong Wen Wang)