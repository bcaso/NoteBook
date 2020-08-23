---
title: strcpy
tags: C,string
grammar_cjkRuby: true
---
* `char * strcpy ( char *restrict destination, const char * source );`
* 把source的字符串拷贝到destination
    * restrict表明source和destination不重叠(C99))
* 返回destination

# Example：
```c?linenums
/* strcpy example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str1[]="Sample string";
  char str2[40];
  char str3[40];
  strcpy (str2,str1);
  strcpy (str3,"copy successful");
  printf ("str1: %s\nstr2: %s\nstr3: %s\n",str1,str2,str3);
  return 0;
}
```
# Output:
```console
str1: Sample string
str2: Sample string
str3: copy successful
```
# 使用场景
常用于给字符数组赋值
字符数组str 或 指针 还可以用`scanf("%s",str);`的形式来赋值。

## scanf()给字符串数组赋值
```c?linenums
#include<stdio.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
	char str[100];
	scanf("%s", str);
	puts(str);
	return 0;
}
```
## scanf()给指针字符串赋值
给指针字符串赋值前必须先开辟一个空间：
```c?linenums
#include<stdio.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
	char *p;
	p = (char *)malloc(sizeof(char) * 100);
	scanf("%s", p);
	puts(p);
	return 0;
}
```
还可以使用`gets(str);`来给字符串赋值。

如果又有指针又有字符数组：
```c?linenums
char *p = NULL;
char str[40];
p = &str;//指针指向数组
gets(str);//给字符数组赋值
strcpy(str,"Hello World!");//给字符数组赋值的另一种方式
```