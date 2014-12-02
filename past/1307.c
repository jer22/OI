#include <stdio.h>
#include <string.h>

int main( void ) {
	char arr[15];
	scanf("%s", arr);
	int l = strlen(arr);
	int s = 0;
	int i, j = l - 1;
	if (arr[0] == '-') {
		printf("-");
		s++;
	}
	while (arr[j--] == '0') {}
	for (i = j + 1 ; i >= s; i--)
		printf("%c", arr[i]);
	system("pause");
	return 0;
}
