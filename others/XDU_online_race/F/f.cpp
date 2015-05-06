#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

bool notpri[1000005];
int pri[100000], tot = 0;
void init() {
	notpri[1] = 1;
	for (int i = 2; i <= 1000000; i++) {
		if (notpri[i]) continue;
		pri[tot++] = i;
		for (int j = i + i; j <= 1000000; j += i)
			notpri[j] = 1;
	}
}

int n;
int dp[1000005];
int main() {
	freopen("f.in", "r", stdin);
	init();
	memset(dp, 0x3f, sizeof(dp));
	dp[1] = 0;
	for (int i = 1; i < 1000000; i++) {
		dp[i + 1] = min(dp[i + 1], dp[i] + 1);
		for (int j = 0; j < tot; j++) {
			if (i * pri[j] > 1000000) break;
			dp[i * pri[j]] = min(dp[i * pri[j]], dp[i] + 1);
		}
	}
	while (~scanf("%d", &n)) {
		printf("%d\n", dp[n]);
	}

	return 0;
}
