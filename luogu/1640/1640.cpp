#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int parent[1000010];
int vis[1000010];
int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

void un(int x, int y) {
	if (x < y) swap(x, y);
	vis[y] = 1;
	parent[y] = x;
}

int main() {
	freopen("1640.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++) {
		parent[i] = i;
	}
	int x, y;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x, &y);
		int rx = find(x);
		int ry = find(y);
		if (rx == ry) vis[rx] = 1;
		else un(rx, ry);
	}
	for (int i = 1; i <= n + 1; i++) {
		if (!vis[i]) {
			printf("%d\n", i - 1);
			break;
		}
	}
	return 0;
}
