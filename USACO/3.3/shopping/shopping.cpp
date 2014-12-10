/*
ID:shijiey1
PROG:shopping
LANG:C++
*/

/*
因为n<=5,k<=5,所以用一个5维数组表示dp[wa][wb][wc][wd][we]表示买了wa个a商品，wb个b商品……的最小花费。
然后就记忆搜吧，没什么技术含量。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int s, b, m;
// shop[i][0]表示第i种优惠的价格，shop[i][1],shop[i][2],shop[i][3],shop[i][4],shop[i][5]表示第i种优惠5种商品的个数
// 把商品的原价同样算作优惠放到shop数组里。
int shop[105][6];
int buy[6];
int cc[1005];
int dp[6][6][6][6][6];

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

void scan() {
	scanf("%d", &s);
	int n;
	int t = 0;
	for (int i = 1; i <= s; i++) {
		scanf("%d", &n);
		int c, k, p;
		for (int j = 0; j < n; j++) {
			scanf("%d %d", &c, &k);
			if (!cc[c]) cc[c] = ++t;
			shop[i][cc[c]] = k;
		}
		scanf("%d", &shop[i][0]);
	}
	scanf("%d", &b);
	int c, k;
	for (int i = 1; i <= b; i++) {
		scanf("%d %d %d", &c, &k, &shop[s + i][0]);
		if (!cc[c]) cc[c] = ++t;
		shop[s + i][cc[c]] = 1;
		buy[cc[c]] = k;
	}
	m = s + b;
	memset(dp, -1, sizeof(dp));
	dp[0][0][0][0][0] = 0;
}

int dfs(int wa, int wb, int wc, int wd, int we) {
	if (dp[wa][wb][wc][wd][we] != -1)
		return dp[wa][wb][wc][wd][we];
	int re = INF;
	int na, nb, nc, nd, ne;
	for (int i = 1; i <= m; i++) {
		na = wa - shop[i][1];
		nb = wb - shop[i][2];
		nc = wc - shop[i][3];
		nd = wd - shop[i][4];
		ne = we - shop[i][5];
		if (na < 0 || nb < 0 || nc < 0 || nd < 0 || ne < 0) continue;
		dp[na][nb][nc][nd][ne] = dfs(na, nb, nc, nd, ne);
		re = min(re, dp[na][nb][nc][nd][ne] + shop[i][0]);
	}
	return re;
}

int main() {
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	scan();
	int re = dfs(buy[1], buy[2], buy[3], buy[4], buy[5]);
	printf("%d\n", re);
	return 0;
}
