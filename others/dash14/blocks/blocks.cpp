#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 510

using namespace std;

int n, m;
int arr[MAXN][MAXN];
int parent[MAXN * MAXN +  MAXN];

int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

int un(int p, int q) {
	int tx = find(p);
	int ty = find(q);
	if (tx == ty) return 0;
	parent[tx] = q;
	return 1;
}

int cnt = 0;
int main() {
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= 507 * 507 + 507; i++) {
		parent[i] = i;
	}
	int x, y, c;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &c, &x, &y);
		arr[x][y] = c + 1;
		cnt++;
		if (arr[x - 1][y] == arr[x][y]) {
			cnt -= un(x * 503 + y, (x - 1) * 503 + y);
		}
		if (arr[x + 1][y] == arr[x][y]) {
			cnt -= un(x * 503 + y, (x + 1) * 503 + y);
		}
		if (arr[x][y - 1] == arr[x][y]) {
			cnt -= un(x * 503 + y, x * 503 + y - 1);
		}
		if (arr[x][y + 1] == arr[x][y]) {
			cnt -= un(x * 503 + y, x * 503 + y + 1);
		}
		printf("%d\n", cnt);
	}
	return 0;
}
