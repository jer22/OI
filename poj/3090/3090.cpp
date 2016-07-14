#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n;
int phi[1005];

void getPhi() {
	phi[1] = 1;
	for (int i = 2; i <= 1000; i++) {
		if (phi[i]) continue;
		for (int j = i; j <= 1000; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i * (i - 1);
		}
	}
}

int main() {
	freopen("3090.in", "r", stdin);
	getPhi();
	scanf("%d", &T);
	int cnt = 0;
	while (T--) {
		scanf("%d", &n);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += phi[i] * 2;
		}
		printf("%d %d %d\n", ++cnt, n, ans + 1);
	}


	return 0;
}
