#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char re[255];
char arr[24][24];

int min(int a, int b) {
	return a < b ? a : b;
}

int cmp(const void *a, const void *b) {
	char * a1 = (char *)a;
	char * b1 = (char *)b;
	int la = strlen(a1), lb = strlen(b1);
	int i;
	int bo = 1;
	for (i = 0; i < min(la, lb); i++) {
		if (a1[i] != b1[i]) bo = 0;
	}
	if (bo) {
		if (la > lb) return (a1[lb] - a1[0]);
		return (b1[la] - b1[0]);
	}
	return - strcmp(a1, b1);
}

int main( void ) {
	int n;
	int i;
	int l = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s", &arr[i]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	for (i = 0; i < n; i++) {
		strcpy(&re[l], arr[i]);
		l += strlen(arr[i]);
	}

	printf("%s", re);
	system("pause");
	return 0;
}
