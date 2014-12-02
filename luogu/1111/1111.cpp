#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Road {
	int x, y, t;
	bool operator < (const Road &r) const {
		return t < r.t;
	}
};

int n, m;
int blocks;
Road arr[100010];
int parent[1010];

int find(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

void un(int x, int y) {
	int tx = find(x);
	int ty = find(y);
	if (tx == ty) return;
	parent[tx] = y;
	return;
}

int main() {
	freopen("1111.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}
	blocks = n;
	int a, b, c;
	Road r;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		r.x = a;
		r.y = b;
		r.t = c;
		arr[i] = r;
	}
	sort(arr, arr + m);
	for (int i = 0; i < m; i++) {
		r = arr[i];
		if (find(r.x) != find(r.y)) {
			un(r.x, r.y);
			blocks--;
		}
		if (blocks == 1) {
			printf("%d\n", r.t);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
