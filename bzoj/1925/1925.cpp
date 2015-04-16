#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

int n, p;
long long dp[4205];
long long c[2][4205];
int main() {
	freopen("1925.in", "r", stdin);
	scanf("%d %d", &n, &p);
	dp[1] = 1;
	dp[0] = 1;
	c[0][1] = 1;
	c[0][0] = 1;
	c[1][0] = 1;
	int now = 0, pre = 1;
	for (int i = 2; i <= n; i++) {
		now ^= 1;
		pre ^= 1;
		for (int j = 0; j < i; j++) {
			dp[i] += ((c[now][j] * dp[j]) % p) * dp[i - j - 1];
			dp[i] %= p;
		}
		for (int j = 1; j <= i; j++) {
			c[now][j] = c[pre][j] + c[pre][j - 1];
			c[now][j] %= p;
		}
		dp[i] %= p;
	}
	cout << (dp[n] * 2) % p << endl;
	return 0;
}
