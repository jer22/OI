#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n;
int arr[100005], dp[100005], head[100005];
int main() {
	freopen("1003.in", "r", stdin);
	cin >> T;
	int cas = 1;
	while (T--) {
		memset(dp, 0, sizeof(dp));
		memset(head, 0, sizeof(head));
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> arr[i];
		head[0] = 1;
		int ans = -1111111;
		int idx = 0;
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
		printf("Case %d:\n%d %d %d\n", cas++, ans, head[idx], idx);
		if (T) cout << endl;
	}
	return 0;
}
