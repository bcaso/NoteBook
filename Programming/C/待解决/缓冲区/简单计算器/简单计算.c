#include <stdio.h>
#include<conio.h>
int main(void) {
	int num1, num2;
	char symbol;
	//方法一：
	//scanf_s("%d %c %d", &num1, &symbol, &num2);

	/* 方法二
	scanf_s("%d ", &num1);
	symbol = _getche();
	scanf_s("%d", &num2);
	*/

	//方法三
	scanf_s("%d ", &num1);
	symbol = getchar();
	scanf_s("%d", &num2);


	if (symbol == '+') {
		printf("%d\n", num1 + num2);
	}
	else if (symbol == '-') {
		printf("%d\n", num1 - num2);
	}
	else if (symbol == '*') {
		printf("%d\n", num1 * num2);
	}
	else if (symbol == '/') {
		printf("%d\n", num1 / num2);
	}
	else if (symbol == '%') {
		printf("%d\n", num1 % num2);
	}
	else {
		printf("ERROR\n");
	}

	printf("\nPress any to continue...");
	_getch();
	return 0;
}