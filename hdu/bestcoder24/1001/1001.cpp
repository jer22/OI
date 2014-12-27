#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[1005];
int prime[1005];

int main() {
	freopen("1001.in", "r", stdin);
	for (int i = 2; i <= 1002; i++) {
		for (int j = i + i; j <= 1002; j += i) {
			prime[j] = 1;
		}
	}
	while (~scanf("%d", &n)) {
		long long ans = 0;
		int t;
		for (int i = 0; i < n; i++) {
			scanf("%d", &t);
			if (!prime[t]) ans += t;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
