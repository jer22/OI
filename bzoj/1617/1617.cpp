#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 2505;
const int INF = 0x3f3f3f3f;

int n, m;
int dp[MAXN];
int arr[MAXN];
int sum[MAXN];
int main() {
	freopen("1617.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
		dp[i] = sum[i] + m;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			dp[j] = min(dp[j], dp[i] + sum[j - i] + m * 2);
		}
	}
	cout << dp[n] << endl;

	return 0;
}
