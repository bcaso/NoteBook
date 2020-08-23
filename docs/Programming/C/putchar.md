---
title: putchar
tags: C,字符串
grammar_cjkRuby: true
---
* `int putchar(int c);`
* 向标准输出写一个字符
* 返回写了几个字符，`EOF(-1)`表示写失败

# Example

```c
/* putchar example: printing the alphabet */
#include <stdio.h>

int main ()
{
  char c;
  for (c = 'A' ; c <= 'Z' ; c++) putchar (c);

  return 0;
}
```