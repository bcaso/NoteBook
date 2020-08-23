---
title: strtok字符串分解
tags: C,string,Function
grammar_cjkRuby: true
---
原型：char *strtok(char *s, char *delim);

功能：分解字符串为一组标记串。s为要分解的字符串，delim为分隔符字符串。

说明：首次调用时，s必须指向要分解的字符串，随后调用要把s设成NULL。 strtok在s中查找包含在delim中的字符并用NULL('\0')来替换，直到找遍整个字符串。 返回指向下一个标记串。当没有标记串时则返回空字符NULL。

```c?linenums

#include <iostream>
using namespace std;
 
int main(int argc, char * argv[])
{
	//时间格式 2010/08/11 10:38:22
	char strEventTime[] = "2010/08/11 10:38:22";
	char *token = NULL;
	
 	token = strtok(strEventTime, "/");
	char *year = token;
	if (token != NULL)
	{
		token = strtok(NULL, "/");
	}
	char *month = token;
	if (token != NULL)
	{
		token = strtok(NULL, " ");
	}
	char *day = token;
	if (token != NULL)
	{
		token = strtok(NULL, ":");
	}
	char *hour = token;
	if (token != NULL)
	{
		token = strtok(NULL, ":");
	}
	char *minute = token;
 
	if (token != NULL)
	{
		token = strtok(NULL, ":");
	}
	char *second = token;
 
	printf("%s %s %s %s %s %s %s\n", year, month, day, hour, minute, second);
    return 0;
}
```