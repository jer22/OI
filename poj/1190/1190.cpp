#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

int minv[22], mins[22];
int n, m;
int ans;

void dfs(int step, int sumv, int sums, int r, int h) {
	if (!step) {
		if (sumv == n) ans = min(sums, ans);
		return;
	}
	if (sumv + minv[step - 1] > n || sums + mins[step - 1] > ans || (2 * (n - sumv) / r + sums >= ans))
		return;
	for (int i = r - 1; i >= step; i--) {
		if (step == m) sums = i * i;
		int maxh = min(h - 1, (n - sumv - minv[step - 1]) / (i * i));
		for (int j = maxh; j >= step; j--) {
			dfs(step - 1, sumv + i * i * j, sums + 2 * i * j, i, j);
		}
	}
}

int main() {
	freopen("1190.in", "r", stdin);
	for (int i = 1; i < 22; i++) {
		minv[i] = minv[i - 1] + i * i * i;
		mins[i] = mins[i - 1] + i * i * 2;
	}
	scanf("%d %d", &n, &m);
	ans = INF;
	dfs(m, 0, 0, n + 1, n + 1);
	if (ans == INF) cout << 0 << endl;
	else cout << ans << endl;
	return 0;
}
