#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int edges[1010][1010];
int parent[1010];
int set[1010];
int vis[1010];
int ans[1010];

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void un(int x, int y) {
	parent[find(x)] = find(y);
}

int main() {
	freopen("off.in", "r", stdin);
	freopen("off.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a][b] = edges[b][a] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!edges[i][j]) un(i, j);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		set[i] = find(i);
		if (!vis[set[i]]) {
			cnt++;
			vis[set[i]] = 1;
		}
	}
	sort(set + 1, set + n + 1);
	printf("%d\n", cnt);
	int temp = set[1];
	int t = 0;
	int idx = 0;
	for (int i = 1; i <= n; i++) {
		if (set[i] == temp) t++;
		else {
			ans[idx++] = t;
			temp = set[i];
			t = 1;
		}
	}
	ans[idx++] = t;
	sort(ans, ans + idx);
	for (int i = 0; i < idx; i++) {
		if (i) printf(" ");
		printf("%d", ans[i]);
	}
	printf("\n");
	return 0;
}
