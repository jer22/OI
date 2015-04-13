#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int T, n, m, k;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int ans[8][8];

struct Node{
	int color, cnt;
	bool operator < (const Node &n) const {
		return cnt > n.cnt;
	}
};

Node c[30];
bool check(int x, int y, int co) {
	for (int i = 0; i < 4; i++) {
		if (co == ans[x + dir[i][0]][y + dir[i][1]]) return false;
	}
	return true;
}

void print() {
	printf("YES\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (j != 1) printf(" ");
			printf("%d", ans[i][j]);
		}
		printf("\n");
	}
}

int tim = 0;
bool dfs(int x, int y) {
	tim++;
	if (tim >= 30000) return false;
	if (y == m + 1) {
		y = 1;
		x++;
	}
	if (x == n + 1) {
		print();
		return true;
	}
	for (int i = 1; i <= k; i++) {
		if (!c[i].cnt) continue;
		if (!check(x, y, c[i].color)) continue;
		ans[x][y] = c[i].color;
		c[i].cnt--;
		if (dfs(x, y + 1)) return true;
		c[i].cnt++;
		ans[x][y] = 0;
	}
	return false;
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		tim = 0;
		printf("Case #%d:\n", cas++);
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 1; i <= k; i++) {
			scanf("%d", &c[i].cnt);
			c[i].color = i;
		}
		sort(c + 1, c + k + 1);
		memset(ans, 0, sizeof(ans));
		if (!dfs(1, 1)) {
			printf("NO\n");
		}

	}

	return 0;
}
