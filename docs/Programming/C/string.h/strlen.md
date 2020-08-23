---
title: strlen
tags: C,string
grammar_cjkRuby: true
---

* `size_t strlen(const char *s);`
    * `const char *s` 表示该函数不会修改传入的字符串
* 返回s的字符长度(不包括结尾的0)

```c?linenums
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
    char line[] = "Hello";
    printf("strlen=%lu\n", strlen(line));//Display strlen=5
    printf("strlen=%lu\n", sizeof(line));//Display sizeof=6  sizeof包含这个字符串结尾的 \0
}
```
# Strlen()
```
　　原型：extern int strlen(char *s);

　　用法：#include <string.h>

　　功能：计算字符串s的(unsigned int型）长度

　　说明：返回s的长度，不包括结束符NULL。
　　
```
## 实现strlen函数的源代码
### 第一种
```c?linenums
int myStrlen(const char *s) // 得到字符串的长度
{
    int len = 0;
    while(s[len])   // 把指针当作数组来用
    {
        len++;
    }
    return len;
}
```
### 第二种
```c?linenums
int myStrlen( char *str)
{
    int length = 0;
    while(*str)
    {
        str++;
        length++;
    }
    return length;
}
```
### 第三种
```c?linenums
#include <stdio.h>
#include <stdlib.h>
int my_strlen(char * str)
{
    int count = 0;
    if(str == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while(*str++ != '\0')
    {
        count++;
    }
    return count;
}
int main ()
{
    char *p = "andef";
    int ret = my_strlen(p);
    printf("%d\n",ret);
    return 0;
}
```
# 分析
上面的三种你觉得好吗？如果满分10分，也许你只能拿到5分，甚至不及格。
<br>
（1）若函数定义`int my_strlen(char * str) ` 中不加  **const** ，那么从主函数中传的实参p的内容在函数定义时就可以很容易被改变，如果加了 **const**  ，一旦实参的值被改变编译器就会报错。
<br>
（2）若实参是一个空指针，你觉得编译时会报错吗？不会的！而且函数里用if语句来检测NULL，无论实参是否为NULL，一调用函数时都得对实参进行判断，若实参不为NULL，那么我们就不需要进行判断了。这就引入了断言函数，**assert：有规则地判断指针的有效性，帮助程序员很好定位问题**，但它不会为程序员解决问题。如果我们用`assert(str != NULL);`代替if语句，那么assert函数就会有规则地帮我们进行判断，若实参不是NULL，则直接跳过assert函数，并执行下一条指令；如果是实参NULL，那么就要引入Release版本和Debug版本了，在Release版本下，运行编译器不会报出错误；而在Debug版本下，编译器就会报出错，说明问题错在哪儿。我们一般在Release版本和Debug版本下使用assert函数，**Debug称为调试版本**，它包含调试信息，但它不做任何的优化，便于程序员调试程序；**Release称为发布版本**，它往往是进行了各种优化，使得程序在代码大小和运行速度上都是最优的，以便用户很好的使用。

经过分析后，我们看一下这个函数应该怎么写。
## 较完美的写法
```c?linenums
#include <stdio.h>
#include <assert.h>
int my_strlen(char const * str)
{
    int count = 0;
    assert(str != NULL);
    while(*str++ != '\0')
    {
        count++;
    }
    return count;
}
int main ()
{
    char *p = "andef";
    int ret = my_strlen(p);
    printf("%d\n",ret);
    return 0;
}
```
这样的程序，刚入门时能这样写已经不错了！ 
在使用断言函数时必须引入头文件`assert.h`！