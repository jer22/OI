#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m, p;
int parent[5010];

int find(int r) {
	if (r == parent[r]) return r;
	return parent[r] = find(parent[r]);
}

void un(int x, int y) {
	int tx = find(x);
	int ty = find(y);
	if (tx == ty) return;
	parent[tx] = y;
	return;
}

int main() {
	freopen("1551.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &p);
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		un(a, b);
	}
	for (int i = 0; i < p; i++) {
		scanf("%d %d", &a, &b);
		if (find(a) == find(b)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}
