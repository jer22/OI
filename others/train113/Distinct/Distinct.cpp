#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

struct Point{
	int x, y;
};

int n;
int ax, bx, cx;
int ay, by, cy;
int x, y;
int now = 1;
int i = 1;
map<map<int, int>, int> vis;
int main() {
	freopen("distinct.in", "r", stdin);
	// freopen("distinct.out", "w", stdout);
	scanf("%d", &n);
	scanf("%d %d %d %d %d %d %d %d", &x, &ax, &bx, &cx, &y, &ay, &by, &cy);
	map<int, int> point;
	point[x] = y;
	vis[point] = 1;
	map<int, int> p;
	while (now < n) {
		i++;
		x = (x * ax + bx + i - 1) % cx;
		y = (y * ay + by + i - 1) % cy;
		p.clear();
		p[x] = y;
		if (vis[p])continue;
		now++;
		vis[p] = 1;
	}
	printf("%d\n", i);
	return 0;
}
