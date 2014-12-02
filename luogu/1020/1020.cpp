#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int n = 0;
int arr[2000];
int decrease[2000];
int increase[2000];
int maxLenDec = 0;
int maxLenInc = 0;

int find_dec(int num) {
	int l = 0;
	int r = maxLenDec;
	while (l < r) {
		int c = ((l + r) >> 1) + 1;
		if (num >= decrease[c]) {
			r = c - 1;
		} else {
			l = c;
		}
	}
	if (!decrease[l + 1]) {
		maxLenDec++;
	}
	return l + 1;
}

int find_inc(int num) {
	int l = 0;
	int r = maxLenInc;
	while (l < r) {
		int c = ((l + r) >> 1) + 1;
		if (num < increase[c]) {
			r = c - 1;
		} else {
			l = c;
		}
	}
	if (!increase[l + 1]) {
		maxLenInc++;
	}
	return l + 1;
}

int main() {
	freopen("1020.in", "r", stdin);
	memset(decrease, 0, sizeof(decrease));
	memset(increase, 0, sizeof(increase));
	while (cin >> arr[++n]);
	n--;
	decrease[0] = INF;

	for (int i = 1; i <= n; i++) {
		int k = find_dec(arr[i]);
		// printf("%d %d\n", k, maxLenDec);
		decrease[k] = arr[i];
		// for (int i = 0; i <= maxLenDec; i++) {
		// 	printf("%d ", decrease[i]);
		// }
		// printf("\n-----\n");
		k = find_inc(arr[i]);
		// printf("%d %d\n", k, maxLenInc);
		increase[k] = arr[i];
	// 	for (int i = 0; i <= maxLenInc; i++) {
	// 		printf("%d ", increase[i]);
	// 	}
	// 	printf("\n-----\n");
	}
	printf("%d\n%d\n", maxLenDec, maxLenInc);
	return 0;
}
