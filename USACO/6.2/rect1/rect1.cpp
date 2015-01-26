/*
ID:shijiey1
LANG:C++
PROG:rect1
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Rect{
	int x1, y1, x2, y2;
	int color;
	void init(int a, int b, int c, int d, int col) {
		x1 = a, y1 = b, x2 = c, y2 = d, color = col;
	}
};

int n;
Rect rect[1005];
int ans[2505];
bool vis[2505];

int dfs(int now, Rect k) {
	if (now == n)
		return (k.x2 - k.x1) * (k.y2 - k.y1);
	int area = 0;
	Rect cut = rect[now + 1];
	Rect base = k;
	// if (base.color == cut.color) area += dfs(now + 1, cut);
	if (cut.x2 <= base.x1 || cut.x1 >= base.x2 || cut.y2 <= base.y1 || cut.y1 >= base.y2) {
		return dfs(now + 1, k);
	}
	Rect t;
	if (cut.x1 > base.x1 && cut.x1 < base.x2) {
		t.init(base.x1, base.y1, cut.x1, base.y2, base.color);
		area += dfs(now + 1, t);
		base.x1 = cut.x1;
	}
	if (cut.x2 > base.x1 && cut.x2 < base.x2) {
		t.init(cut.x2, base.y1, base.x2, base.y2, base.color);
		area += dfs(now + 1, t);
		base.x2 = cut.x2;
	}
	if (cut.y1 > base.y1 && cut.y1 < base.y2) {
		t.init(base.x1, base.y1, base.x2, cut.y1, base.color);
		area += dfs(now + 1, t);
		base.y1 = cut.y1;
	}
	if (cut.y2 > base.y1 && cut.y2 < base.y2) {
		t.init(base.x1, cut.y2, base.x2, base.y2, base.color);
		area += dfs(now + 1, t);
	}
	return area;
}


int main() {
	freopen("rect1.in", "r", stdin);
	freopen("rect1.out", "w", stdout);
	rect[0].x1 = rect[0].y1 = 0;
	rect[0].color = 1;
	scanf("%d %d %d", &rect[0].x2, &rect[0].y2, &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d %d %d %d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2, &rect[i].color);
	for (int i = 0; i <= n; i++) {
			ans[rect[i].color] += dfs(i, rect[i]);

	}
	for (int i = 1; i <= 2500; i++)
		if (ans[i]) cout << i << ' ' << ans[i] << endl;

	return 0;
}
