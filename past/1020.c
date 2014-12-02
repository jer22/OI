#include <stdio.h>
#include <string.h>

int arr[1024];

int inc(int *a, int n) {
	int maxlen = 0;
	int i, j;
	int len[1024];
	memset(len, 0, sizeof(len));
	for (i = 1; i < n; i++) {
		for (j = i - 1; j >= 1; j--) {
			if (a[j] < a[i] && len[j] > len[i])
				len[i] = len[j];
		}
		len[i]++;
		if (len[i] > maxlen)
			maxlen = len[i];
	}
	return maxlen;
}

int dec(int *a, int n) {
	int maxlen = 0;
	int i, j;
	int len[1024];
	memset(len, 0, sizeof(len));
	for (i = 1; i < n; i++) {
		for (j = i - 1, j >= 1; j--) {
			if (a[j] > a[i] && len[j] > len[i])
				len[i] = len[j];
		}
		len[i]++;
		if (maxlen < len[i])
			maxlen = len[i];
	}
	return maxlen;
}

int main( void ) {
	int i = 1, j;
	scanf("%d", &arr[0]);
	while (getchar() != '\n') {
		scanf("%d", &arr[i++]);
	}
	int n = i;

	printf("%d\n%d", dec(arr, n - 1), inc(arr, n - 1));
	system("pause");
	return 0;
}
