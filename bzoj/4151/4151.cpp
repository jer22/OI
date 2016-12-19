#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005;

int T, n, m;
vector<int> edges[MAXN];
int deep[MAXN], fa[MAXN][22];

void dfs(int x, int pre) {
	fa[x][0] = pre;
	deep[x] = deep[pre] + 1;
	for (int i = 1; i < 21; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0, nex; i < edges[x].size(); i++) if ((nex = edges[x][i]) != pre) {
		dfs(nex, x);
	}
}

int get_lca(int a, int b) {
	if (deep[a] < deep[b]) swap(a, b);
	for (int t = deep[a] - deep[b], i = 0; i < 21; i++) {
		if ((t >> i) & 1) a = fa[a][i];
	}

	for (int x = 20; ~x; x--) {
		if (fa[a][x] != fa[b][x]) a = fa[a][x], b = fa[b][x];
	}
	if (a != b) return fa[a][0];
	return a;
}

int dist(int a, int b) {
	int lca = get_lca(a, b);
	return deep[a] + deep[b] - (deep[lca] << 1);
}

int getfa(int x, int len) {
	for (int i = 0; i < 21; i++)
		if ((len >> i) & 1) x = fa[x][i];
	return x;
}

struct Node{
	int a, b, d;
	Node() {}
	Node(int _, int __, int ___) : a(_), b(__), d(___) {}
} query[MAXN];
int main() {
	freopen("4151.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
		}
		for (int i = 1, a, b; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		dfs(1, 0);
		bool flag = true;
		int idx = 0, mx = -1;
		for (int i = 0, a, b, d; i < m; i++) {
			scanf("%d %d %d", &a, &b, &d);
			if (dist(a, b) > d) flag = false;
			if (!flag) continue;
			int t = max(0, dist(1, a) + dist(1, b) - d);
			if (t > mx) mx = t, idx = i;
			query[i] = Node(a, b, d);
		}
		if (!flag) {
			printf("NIE\n");
			continue;
		}
		int a = query[idx].a, b = query[idx].b, d = query[idx].d;
		int lca = get_lca(a, b);
		while (fa[lca][0] && (dist(fa[lca][0], a) + dist(fa[lca][0], b) <= d)) lca = fa[lca][0];
		for (int i = 0; i < m; i++) {
			if (dist(query[i].a, lca) + dist(query[i].b, lca) > query[i].d) {
				flag = false;
				break;
			}
		}
		if (flag) printf("TAK %d\n", lca);
		else printf("NIE\n");
	}


	return 0;
}
