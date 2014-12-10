/*
ID:shijiey1
PROG:inflate
LANG:C++
*/

/*
裸的完全背包完全背包完全背包。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int m, n;
int sco[10010];
int tim[10010];
int dp[10010];
int main() {
	freopen("inflate.in", "r", stdin);
	freopen("inflate.out", "w", stdout);
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &sco[i], &tim[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = tim[i]; j <= m; j++) {
			dp[j] = max(dp[j], dp[j - tim[i]] + sco[i]);
		}
	}
	printf("%d\n", dp[m]);
	return 0;
}
