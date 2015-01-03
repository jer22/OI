#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

#define INF 0x3f3f3f3f

using namespace std;

int T;
int n;
string name[17];
int dead[17];
int tim[17];
int dp[65550];
int tot[65550];
int pre[65550];

void print(int now) {
	if (!now) return;
	print(now - (1 << (pre[now])));
	cout << name[pre[now]] << endl;
}

int main() {
	freopen("1074.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			cin >> name[i] >> dead[i] >> tim[i];
		int m = 1 << n;
		for (int i = 1; i < m; i++) {
			dp[i] = INF;
			for (int j = n - 1; j >= 0; j--) {
				int tmp = 1 << j;
				if (!(i & tmp)) continue;
				int score = max(0, tot[i - tmp] + tim[j] - dead[j]);
				if (dp[i] > dp[i - tmp] + score) {
					dp[i] = dp[i - tmp] + score;
					tot[i] = tot[i - tmp] + tim[j];
					pre[i] = j;
				}
			}
		}
		cout << dp[m - 1] << endl;
		print(m - 1);
	}


	return 0;
}
