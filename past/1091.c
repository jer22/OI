#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr[102];

int inc(int *a, int n) {
	int i, j;
	int maxlen = 0;
	int len[102];
	memset(len, 0, sizeof(len));
	for (i = 1; i <= n; i++) {
		for (j = i - 1; j >= 1; j--) {
			if (a[j] < a[i] && len[j] > len[i]) {
				len[i] = len[j];
			}
		}
		len[i]++;
		if (len[i] > maxlen)
			maxlen = len[i];
	}
	return maxlen;
}

int dec(int *a, int start, int end) {
	int i, j;
	int maxlen = 0;
	int len[102];
	memset(len, 0, sizeof(len));
	for (i = start; i <= end; i++) {
		for (j = i - 1; j >= start; j--) {	
			if (a[j] > a[i] && len[j] > len[i]) {
				len[i] = len[j];
			}
		}
		len[i]++;
		if (len[i] > maxlen)
			maxlen = len[i];
	}
	return maxlen;
}

int main( void ) {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	int min = n, temp;
	for (i = 1; i <= n; i++) {
		temp = (n - inc(arr, i) - dec(arr, i + 1, n));
		if (temp < min)
			min = temp;
	}
	printf("%d", min);
	return 0;
}
