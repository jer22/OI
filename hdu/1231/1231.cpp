#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int dp[10011];
int arr[10011];
int head[10011];
int n;
int main() {
	while (~scanf("%d", &n) && n) {
		memset(dp, 0, sizeof(dp));
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= n; i++)
			cin >> arr[i];
		int ans = -1111111;
		int idx = 0;
		head[0] = 1;
		for (int i = 1; i <= n; i++) {
			if (arr[i] > dp[i - 1] + arr[i]) {
				dp[i] = arr[i];
				head[i] = i;
			} else {
				dp[i] = dp[i - 1] + arr[i];
				head[i] = head[i - 1];
			}
			if (dp[i] > ans) {
				ans = dp[i];
				idx = i;
			}
		}
		if (dp[idx] < 0) {
			cout << 0 << ' ' << arr[1] << ' ' << arr[n] << endl;
		} else cout << dp[idx] << ' ' << arr[head[idx]] << ' ' << arr[idx] << endl;
	}
	return 0;
}
