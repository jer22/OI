#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

int T;
char s1[1000005], s2[1005];
int l1, l2;

int dp[1005][1005];
vector<int> pos[30];

int getpos(int low, int x) {
	if (pos[x].size() == 0) return INF;
	int l = 0, r = pos[x].size() - 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (pos[x][mid] > low)
			r = mid;
		else l = mid + 1;
	}

	if (pos[x][l] > low) return pos[x][l];
	return INF;
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s1 + 1);
		scanf("%s", s2 + 1);
		l1 = strlen(s1 + 1);
		l2 = strlen(s2 + 1);
		for (int i = 0; i <= l2; i++)
			for (int j = 0; j <= l2; j++)
				dp[i][j] = INF;
		dp[0][0] = 0;
		for (int i = 0; i <= 26; i++)
			pos[i].clear();
		for (int i = 1; i <= l1; i++) {
			pos[s1[i] - 'a'].push_back(i);
		}
		for (int i = 0; i < l2; i++) {
			for (int j = 0; j <= i; j++) {
				if (dp[i][j] == INF) continue;
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
				dp[i + 1][j + 1] = min(dp[i + 1][j + 1], getpos(dp[i][j], s2[i + 1] - 'a'));
			}
		}
		int ans = 0;
		for (int i = 1; i <= l2; i++)
			if (dp[l2][i] != INF) ans = i;
		cout << ans << endl;
	}


	return 0;
}
