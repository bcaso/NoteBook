---
title: scanf 函数报错
tags: C,Function,IDE
grammar_cjkRuby: true
---
错误提示：error C4996: 'scanf': This function or variable may be unsafe. Consider using scanf_s instead. To disable deprecation, use_CRT_SECURE_NO_WARNINGS. See online help for details.

## 要去除这个错误，有三个方法：

### （1）根据提示

在文件顶部加入一行：#define _CRT_SECURE_NO_WARNINGS
```csharp
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
int main() {
	char s[30];
	char* p;
	scanf("%s", s);
	p = s;
	while (*p != '\0'){ p++; }
	printf("%d\n", p - s);
	while(1);
	return 0;
```
运行成功！

### （2）根据提示：

在文件顶部加入一行：#pragma warning(disable:4996)

```csharp
#pragma warning(disable:4996)
#include "stdio.h"
 
int main() {
	char s[30];
	char* p;
	scanf("%s", s);
	p = s;
	while (*p != '\0'){ p++; }
	printf("%d\n", p - s);
	while(1);
	return 0;
}
```

### （3）真正原因在与vs中的SDL检查。于是可以:右键单击工程文件-->属性(最后一个)-------->  c/c++  ------>SDL checks ------------> no.

![关闭SDL检查](https://i.loli.net/2018/11/01/5bdac7fa33408.jpg)

# 在新建项目时可以把SDL检查勾掉（默认是yes),就可以避免此问题！
![关闭SDL安全检查](https://i.loli.net/2018/11/01/5bdac7fb38864.jpg)