#include <stdio.h>
#include <stdlib.h>

void print(int a) {
	if (!a) printf("xiaoa wins");
	else printf("uim wins");
}

int main( void ) {
	int arr[9];
	char ch;
	int i;
	int n = 0;
	for (i = 0; i <= 10; i++)
		arr[i] = 2;
	ch = getchar();
	i = 0;
	while (ch != '\n') {
		arr[ch - '0'] = i;
		i = !i;
		n++;
		ch = getchar();
	}
	if (arr[1] == arr[2] && arr[2] == arr[3] && arr[2] != 2) {
		print(arr[2]);
	} else if (arr[1] == arr[4] && arr[4] == arr[7] && arr[4] != 2) {
		print(arr[4]);
	} else if (arr[1] == arr[5] && arr[5] == arr[9] && arr[5] != 2) {
		print(arr[5]);
	} else if (arr[2] == arr[5] && arr[5] == arr[8] && arr[5] != 2) {
		print(arr[5]);
	} else if (arr[3] == arr[6] && arr[6] == arr[9] && arr[6] != 2) {
		print(arr[6]);
	} else if (arr[3] == arr[5] && arr[5] == arr[7] && arr[5] != 2) {
		print(arr[5]);
	} else if (arr[4] == arr[5] && arr[5] == arr[6] && arr[5] != 2) {
		print(arr[5]);
	} else if (arr[7] == arr[8] && arr[8] == arr[9] && arr[8] != 2) {
		print(arr[8]);
	} else {
		printf("drew");
	}


	system("pause");
	return 0;
}
