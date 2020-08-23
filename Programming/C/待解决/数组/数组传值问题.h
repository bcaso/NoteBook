#include <stdio.h>
#include<conio.h>
void printfArray(const int array[]);

int main(void) {
	int array[10];
	for (int i = 0; i < 10; i++) { //把1到10循环存入到数组array中
		array[i] = i+1;
	}
	//printfArray(array);
	printfArray(array, sizeof(array) / sizeof(array[0])); // 使用了另一个参数length

	printf("\nPress any key to continue...");
	_getch();
	return 0;
}
/* // 这个函数有问题，传入的数组参数的元素只剩下了array[0] = 1;其他的元素都消失了 
void printfArray(const int array[]) {
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
		printf("%d,", array[i]);
	//	fflush(stdout);
	}
}
*/

/*
打印数组
@param array[] 要打印的数组,const 是为了防止该函数改变数组元素
@param length 数组的长度
*/
void printfArray(const int array[], int length) {
	for (int i = 0; i < length; i++) {
		printf("%d",array[i]);
	}
}