#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int primeTable[10000];
int prime[10000];
int size = 0;
int cnt = 0;
int ans[10000];
void initPrime() {
	memset(primeTable, 0, sizeof(primeTable));
	for (int i = 2; i < 10000; i++) {
		if (!primeTable[i]) {
			for (int j = i << 1; j < 10000; j += i) {
				primeTable[j] = 1;
			}
		}
	}
	for (int i = 2; i <= 10000; i++) {
		if (!primeTable[i]) prime[size++] = i;
	}
}

int main() {
	freopen("1001.in", "r", stdin);
	initPrime();
	while (cin >> n) {
		cnt = 0;
		if (ans[n]) {
			printf("%d\n", ans[n]);
			continue;
		}
		for (int i = 2; i <= n - 4; i++) {
			if (!primeTable[i]) {
				for (int j = i; j <= n - 4; j++) {
					if (!primeTable[j]) {
						if (j <= n - i - j && !primeTable[n - i - j]) {
							cnt++;
						}
					}
				}
			}
		}
		ans[n] = cnt;
		printf("%d\n", cnt);
	}

	return 0;
}
