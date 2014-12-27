#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Block{
	int x, y, z;
	bool operator < (const Block &b) const {
		if (x != b.x) return x > b.x;
		return y > b.y;
	}
};

int n;
Block arr[500];
int dp[500];
int main() {
	freopen("1069.in", "r", stdin);
	int cas = 1;
	while (~scanf("%d", &n) && n) {
		int cnt = 0;
		int x, y, z;
		for (int i = 1; i <= n; i++) {
			cin >> x >> y >> z;
			arr[cnt].x = x, arr[cnt].y = y, arr[cnt++].z = z;
            arr[cnt].x = x, arr[cnt].y = z, arr[cnt++].z = y;
            arr[cnt].x = y, arr[cnt].y = x, arr[cnt++].z = z;
            arr[cnt].x = y, arr[cnt].y = z, arr[cnt++].z = x;
            arr[cnt].x = z, arr[cnt].y = x, arr[cnt++].z = y;
            arr[cnt].x = z, arr[cnt].y = y, arr[cnt++].z = x;
		}
		sort(arr, arr + cnt);
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < cnt; i++)
			dp[i] = arr[i].z;
		int ans = dp[0];
		for (int i = 1; i < cnt; i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (arr[j].x > arr[i].x && arr[j].y > arr[i].y)
					dp[i] = max(dp[i], dp[j] + arr[i].z);
			}
			ans = max(ans, dp[i]);
		}
		printf("Case %d: maximum height = %d\n", cas++, ans);
	}
	return 0;
}
