#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 20005;

int n, m;
vector<int> edges[MAXN];
int fa[MAXN];

int find(int p) {
	if (p == fa[p]) return p;
	return fa[p] = find(fa[p]);
}

void un(int p, int q) {
	fa[find(p)] = find(q);
}

bool vis[MAXN];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		if (edges[i].empty()) continue;
		int t = edges[i][0];
		if (find(i) == find(t)) flag = false;
		for (int k = 1; k < edges[i].size(); k++) {
			int j = edges[i][k];
			if (find(i) == find(j)) flag = false;
			un(t, j);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int t = find(i);
		if (!vis[t])
			ans++;
		vis[t] = 1;
	}
	cout << ans << endl;
	if (!flag) cout << "Unstable" << endl;
	return 0;
}
