#include <bits/stdc++.h>

using namespace std;

int n, m;
int fa[40005];

int find(int p) {
	if (p == fa[p]) return p;
	return fa[p] = find(fa[p]);
}

void un(int p, int q) {
	fa[find(p)] = find(q);
}

bool vis[40005];
int main() {
	freopen("3296.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n + m; i++)
		fa[i] = i;
	int k, t;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &t);
			if (find(i) != find(n + t)) un(i, n + t);
		}
	}
	int ans = -1;
	for (int i = 1; i <= n; i++) {
		t = find(i);
		if (!vis[t]) {
			ans++;
			vis[t] = 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
