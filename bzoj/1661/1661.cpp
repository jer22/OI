#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 105;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		return x < p.x;
	}
};

int n;
char map[MAXN][MAXN];
vector<Point> p;

bool check(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= n) return false;
	if (map[x][y] == 'B') return false;
	return true;
}

int main() {
	freopen("1661.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s", map[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (map[i][j] == 'J') p.push_back(Point(i, j));
	sort(p.begin(), p.end());
	int siz = p.size();
	int ans = 0;
	for (int i = 0; i < siz; i++) {
		for (int j = i + 1; j < siz; j++) {
			Point a = p[i], b = p[j];
			int dx = abs(a.x - b.x), dy = abs(a.y - b.y);
			if ((dx + dy) % 2) continue;
			int d = (dx - dy) / 2;
			if (a.y >= b.y) {
				int nx1 = a.x + d, ny1 = b.y - d;
				int nx2 = b.x - d, ny2 = a.y + d;
				if (!check(nx1, ny1) || !check(nx2, ny2)) continue;
				if (map[nx1][ny1] != 'J' && map[nx2][ny2] != 'J') continue;
				ans = max(ans, (dx * dx + dy * dy) / 2);
			} else {
				int nx1 = b.x - d, ny1 = a.y - d;
				int nx2 = a.x + d, ny2 = b.y + d;
				if (!check(nx1, ny1) || !check(nx2, ny2)) continue;
				if (map[nx1][ny1] != 'J' && map[nx2][ny2] != 'J') continue;
				ans = max(ans, (dx * dx + dy * dy) / 2);
			}
		}
	}
	cout << ans << endl;

	return 0;
}
