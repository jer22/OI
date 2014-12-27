#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[5005];
int dp[300011];
int main() {
	freopen("1171.in", "r", stdin);
	while (~scanf("%d", &n) && n >= 0) {
		int sum = 0;
		int a, b;
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			sum += a * b;
			while (b--) arr[cnt++] = a;
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < cnt; i++) {
			for (int j = sum / 2; j >= arr[i]; j--) {
				dp[j] = max(dp[j], dp[j - arr[i]] + arr[i]);
			}
		}
		cout << sum - dp[sum / 2] << ' ' << dp[sum / 2] << endl;
	}


	return 0;
}
