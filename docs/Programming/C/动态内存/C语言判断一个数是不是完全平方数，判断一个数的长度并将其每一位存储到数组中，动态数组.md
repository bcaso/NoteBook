---
title: C语言判断一个数是不是完全平方数，判断一个数的长度并将其每一位存储到数组中，动态数组
tags: C,malloc
grammar_cjkRuby: true
---
题目：
>输入n1, n2;
判断n1 到 n2间的符合条件的数（是完全平方数且满足有两个位上的数字相同）的个数。
输出个数。
main函数已经编写好，请实现`IsTheNumber(const int N);`

```c?linenums
#include <stdio.h>
#include<conio.h>
#include<math.h>
int IsTheNumber(const int N);
int IsTheNumber1(const int N);
// 输入示例：143 145
// 输出 cnt = 1

int main(void) {
	int n1, n2, i, cnt;
	scanf("%d %d", &n1, &n2);
	cnt = 0;
	for (i = n1; i <= n2; i++) {
		//if (IsTheNumber(i))cnt++;
		if (IsTheNumber1(i))cnt++;
	}
	printf("cnt = %d\n", cnt);
	printf("\nPress any key to continue...");
	getch();
	return 0;
}

int IsTheNumber(const int N) {
	int  temp;
	int j, k,
		isEqual = 0, isSqrt = 0;
	if (N <= 0)		return 0;

	//把该数每个位上的数都存放到数组中。
	int arr[10];
	temp = N;
	for (j = 0; j < 10; j++) {
		arr[j] = temp % 10;
		temp /= 10;
		//temp == 0时，数组就已经将需要的数存储完毕,存储最后一有效数据的后一位当作数组的长度
		if (temp == 0) { temp = j + 1; break; }
	}

	//判断这个数组中是否有两个数相同
	for (j = 0; j < temp; j++) {
		for (k = j + 1; k < temp; k++) {
			if (arr[j] == arr[k]) { isEqual = 0;	break; }
			else isEqual = 1;
		}
	}
	//判断n是不是完全平方数，利用恒等式： 1+3+5+7+....+(2*n-1)=n^2
	temp = N;
	for (j = 1; j <= temp; j += 2)	temp -= j;
	if (temp == 0)	isSqrt = 1;
	else	isSqrt = 0;

	if (isEqual&&isSqrt) return 1;
	else return 0;
}

int IsTheNumber1(const int N) {
	int  temp;
	int i, j,
		isEqual = 0, isSqrt = 0,
		length = 1;//数组长度
	if (N <= 0)	return 0;

	//判断一个数的个数
	temp = N;
	while (temp >= 10) {
		temp /= 10;
		length++;
	}
	//TODO 用malloc定义一个动态数组，然后把每位上的数存下来，再进行判断
	//int*arr =  (int *)malloc(length * sizeof(int));
	int *arr;
	if ((arr = (int*)malloc(length * sizeof(int))) == NULL) {
		printf("内存空间分配失败，程序退出！");
		return 0;
	}
	temp = N;
	for (i = 0; i < length; i++) {
		*arr++ = temp % 10;
		temp /= 10;
	}

	//判断一个数中是否有两个数相同
	for (i = 0; i < length; i++) {
		for (j = i + 1; j < length; j++) {
			if (arr[i] == arr[j]) { isEqual = 0;	break; }
			else isEqual = 1;
		}
	}
	free(arr);//为什么这个报错？这个代码，如果是在Code:blocks下就不报错，在vs2017下就会报错。
	//判断这个数是不是完全平方数,方法，判断这个数的平方根是否为整数
	if (sqrt(N) == (int)sqrt(N))isSqrt = 1;
	
	if (isEqual&&isSqrt) return 1;
	else return 0;
}
```
