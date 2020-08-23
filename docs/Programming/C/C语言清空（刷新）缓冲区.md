---
title: C语言清空（刷新）缓冲区
tags: C,Function
grammar_cjkRuby: true
---
# 清空输出缓冲区
清空输出缓冲区很简单，使用下面的语句即可：
```c
fflush(stdout);
```
flush() 是一个专门用来清空缓冲区的函数，stdout 是 standard output 的缩写，表示标准输出设备，也即显示器。整个语句的意思是，清空标准输入缓冲区，或者说清空显示器的缓冲区。

Windows 平台下的 printf()、puts()、putchar() 等输出函数都是不带缓冲区的，所以不用清空，下面的代码演示了如何在 Linux 和 Mac OS 平台下清空缓冲区：
```c?linenums
#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("C语言中文网");
    fflush(stdout);  //本次输出结束后立即清空缓冲区
    sleep(5);
    printf("http://c.biancheng.net\n");
   
    return 0;
}
```
程序运行后，第一个 pirntf() 立即输出，等待 5 秒以后，第二个 printf() 才输出，这就符合我们的惯性思维了。如果不加fflush(stdout)语句，程序运行后，第一个 printf() 并不会立即输出，而是等待 5 秒以后和第二个 scanf() 一起输出（已在《C语言数据输出大汇总以及轻量进阶》中进行了演示），这有点不符合我们的思维习惯。

# 清空输入缓冲区
## 1) 使用 getchar() 清空缓冲区
```c
int c;
while((c = getchar()) != '\n' && c != EOF);
```
该代码不停地使用 getchar() 获取缓冲区中的字符，直到遇见换行符\n或者到达文件结尾才停止。由于大家所学知识不足，这段代码暂时无法理解，我也就不细说了，在实际开发中，大家按照下面的形式使用即可：
```c
#include <stdio.h>
int main()
{
    int a = 1, b = 2;
    char c;

    scanf("a=%d", &a);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区
    scanf("b=%d", &b);
    printf("a=%d, b=%d\n", a, b);
   
    return 0;
}
```
输入示例：
```
a=100↙
b=200↙
a=100, b=200
```
按下第一个回车键后，只有第一个 scanf() 读取成功了，第二个 scanf() 并没有开始读取，等我们再次输入并按下回车键后，第二个 scanf() 才开始读取，这就符合我们的操作习惯了。如果没有清空缓冲区的语句，按下第一个回车键后，两个 scanf() 都读取了，只是第二个 scanf() 读取失败了，让人觉得很怪异，这点已在《使用scanf从键盘输入数据》中进行了演示。

改变输入方式，再次尝试一下：
```
a=100b=200↙
b=300↙
a=100, b=300
```
你看，第一次输入的多余内容并没有起作用，就是因为它们在第二个 scanf() 之前被清空了。

<font color = "red">这种方案的关键之处在于，getchar() 是带有缓冲区的，并且一切字符通吃，或者说一切字符都会读取，不会忽略。不过这种方案有个缺点，就是要额外定义一个变量 c，对于有强迫症的读者来说可能有点难受。 </font>

## 2) 使用 scanf() 清空缓冲区
```c
scanf("%*[^\n]"); scanf("%*c");
```
例：
```c
#include <stdio.h>
int main()
{
    int a = 1, b = 2;
   
    scanf("a=%d", &a);
    scanf("%*[^\n]"); scanf("%*c"); //在下次读取前清空缓冲区
    scanf("b=%d", &b);
    printf("a=%d, b=%d\n", a, b);
   
    return 0;
}
```

