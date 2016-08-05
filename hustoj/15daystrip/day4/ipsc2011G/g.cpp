#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 4096;
const int N = 4096;

int r, q;
int que[20005][8];
vector<pair<int, int> > c[4105][4105];
int now = 0, tik = 0;
int lowbit(int x) {
	return x & (-x);
}

void add(int x, int y, int p) {
	for (int i = x; i <= N; i += lowbit(i)) {
		for (int j = y; j <= N; j += lowbit(j)) {
			int val = 0;
			if (!c[i][j].empty()) val = c[i][j].back().second;
			val += p;
			c[i][j].push_back(make_pair(now, val));
		}
	}
}

int low(int x, int y, int tim) {
	if (c[x][y].empty()) return 0;
	int l = 0, r = c[x][y].size() - 1;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (c[x][y][mid].first <= tim)
			l = mid;
		else r = mid - 1;
	}
	if (c[x][y][l].first <= tim)
		return c[x][y][l].second;
	else return 0;
}

int getsum(int x, int y, int tim) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		for (int j = y; j > 0; j -= lowbit(j)) {

			ans += low(i, j, tim);
		}
	}
	return ans;
}

int main() {
	freopen("g.in", "r", stdin);
	freopen("g.out", "w", stdout);
	scanf("%d %d", &r, &q);
	int cnt = 0, tot = 0;
	for (int i = 0; i < q; i++) {
		scanf("%d", &que[i][0]);
		if (que[i][0] == 1)
			scanf("%d %d %d", &que[i][1], &que[i][2], &que[i][3]);
		else {
			scanf("%d %d %d %d %d", &que[i][1], &que[i][2], &que[i][3], &que[i][4], &que[i][5]);
			tot++;
		}
	}
	tot *= r;
	while (r--) {
		for (int i = 0; i < q; i++) {
			if (que[i][0] == 1) {
				now++;
				int x = (que[i][1] ^ tik) % 4096 + 1;
				int y = (que[i][2] ^ tik) % 4096 + 1;
				add(x, y, que[i][3]);
				tik = getsum(x, y, now) - getsum(x - 1, y, now) - getsum(x, y - 1, now) + getsum(x - 1, y - 1, now);
			} else {
				int x1 = (que[i][1] ^ tik) % 4096 + 1, x2 = (que[i][2] ^ tik) % 4096 + 1;
				int y1 = (que[i][3] ^ tik) % 4096 + 1, y2 = (que[i][4] ^ tik) % 4096 + 1;
				if (x1 > x2) swap(x1, x2);
				if (y1 > y2) swap(y1, y2);
				int t;
				if (que[i][5] == 0) t = now;
				if (que[i][5] > 0) t = que[i][5];
				if (que[i][5] < 0) t = now + que[i][5];
				if (t < 0) t = 0;
				// if (i == 39) cout << t << "ffffffff" << endl;
				int ans = getsum(x2, y2, t) - getsum(x2, y1 - 1, t) - getsum(x1 - 1, y2, t) + getsum(x1 - 1, y1 - 1, t);
				if (ans < 0) return 0;
				tik = ans;
				cnt++;
				if (tot - cnt < 20000)
					printf("%d\n", ans);
			}
			// cout << tik << endl;
		}
	}


	return 0;
}
 