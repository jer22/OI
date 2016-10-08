#include <bits/stdc++.h>

using namespace std;

const int DIFF = 100000;

struct Point{
	int x, y, id;
	Point() {}
	Point(int a, int b, int c) : x(a), y(b), id(c) {}
	bool operator < (const Point &p) const {
		return x < p.x;
	}
};

int n, m, k;
vector<Point> sum[200005];
vector<Point> dif[200005];
long long ans[100005];

void dfs(int x, int y, int dir, long long tim) {
	// cout << x << ' ' << y << endl;
	if (!(x % n) && !(y % m)) {
		return;
	}
	int nx = x, ny = y;
	int ndir;
	if (dir == 1) {
		int t = x - y + DIFF;
		sort(dif[t].begin(), dif[t].end());
		for (int i = 0; i < dif[t].size(); i++) {
			ans[dif[t][i].id] = min(ans[dif[t][i].id], tim + (long long)(dif[t][i].x - x));
		}

		int tt = min(n - x, m - y);
		nx += tt;
		ny += tt;
		if (n - x > m - y) ndir = 4;
		else ndir = 2;
		dfs(nx, ny, ndir, tim + (long long)tt);
	} else if (dir == 2) {
		int t = x + y;
		sort(sum[t].begin(), sum[t].end());
		for (int i = sum[t].size() - 1; i >= 0; i--) {
			ans[sum[t][i].id] = min(ans[sum[t][i].id], tim + (long long)(x - sum[t][i].x));
		}

		int tt = min(x, m - y);
		nx -= tt;
		ny += tt;
		if (x > m - y) ndir = 3;
		else ndir = 1;
		dfs(nx, ny, ndir, tim + (long long)tt);
	} else if (dir == 3) {
		int t = x - y + DIFF;
		sort(dif[t].begin(), dif[t].end());
		for (int i = dif[t].size() - 1; i >= 0; i--) {
			ans[dif[t][i].id] = min(ans[dif[t][i].id], tim + (long long)(x - dif[t][i].x));
		}

		int tt = min(x, y);
		nx -= tt;
		ny -= tt;
		if (x > y) ndir = 2;
		else ndir = 4;
		dfs(nx, ny, ndir, tim + (long long)tt);
	} else if (dir == 4) {
		int t = x + y;
		sort(sum[t].begin(), sum[t].end());
		for (int i = 0; i < sum[t].size(); i++) {
			ans[sum[t][i].id] = min(ans[sum[t][i].id], tim + (long long)(sum[t][i].x - x));
		}
		int tt = min(n - x, y);
		nx += tt;
		ny -= tt;
		if (n - x > y) ndir = 1;
		else ndir = 3;
		dfs(nx, ny, ndir, tim + (long long)tt);
	}


}

int main() {
	freopen("c.in", "r", stdin);
	cin >> n >> m >> k;
	int a, b;
	for (int i = 0; i < k; i++)
		ans[i] = 1000000000000000000;
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &a, &b);
		if (!((a + b) & 1)) {
			sum[a + b].push_back(Point(a, b, i));
			dif[a - b + DIFF].push_back(Point(a, b, i));
		}
	}

	dfs(1, 1, 1, 1ll);
	for (int i = 0; i < k; i++) {
		if (ans[i] == 1000000000000000000) ans[i] = -1;
		cout << ans[i] << endl;
	}


	return 0;
}
