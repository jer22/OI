#include <stdio.h>

int main( void ) {
	char arr[256];
	int n;
	scanf("%d %s", &n, &arr);
	int i;
	for (i = 0; i < strlen(arr); i++) {
		arr[i] = ((arr[i] - 'a' + n) % 26) + 'a';  
	}
	printf("%s", arr);
	return 0;
}
