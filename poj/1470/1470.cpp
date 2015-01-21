#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, q;
vector<int> edges[1000];
int ans[1000];
int lca[1000][1000];
bool notRoot[1000];
bool vis[1000];
int father[1000];

int find(int p) {
	if (p == father[p]) return p;
	return find(father[p]);
}

void dfs(int i) {
	vis[i] = 1;
	for (int j = 0; j < edges[i].size(); j++) {
		int nex = edges[i][j];
		if (!vis[nex]) {
			dfs(nex);
			father[nex] = i;
		}
	}
	for (int j = 1; j <= n; j++) {
		if (vis[j] && !lca[i][j])
			lca[i][j] = lca[j][i] = find(j);
	}
}

int main() {
	freopen("1470.in", "r", stdin);
	while (~scanf("%d", &n)) {
		memset(lca, 0, sizeof(lca));
		memset(ans, 0, sizeof(ans));
		memset(notRoot, 0, sizeof(notRoot));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++) {
			father[i] = i;
			edges[i].clear();
		}
		int v, k, son;
		char ch[100];
		for (int i = 1; i <= n; i++) {
			scanf("%d", &v);
			scanf("%[^0-9]", ch);
			scanf("%d", &k);
			scanf("%[^0-9]", ch);
			for (int i = 0; i < k; i++) {
				scanf("%d", &son);
				edges[v].push_back(son);
				notRoot[son] = true;
			}
		}
		for (int i = 1; i <= n; i++)
			if (!notRoot[i]) dfs(i);
		scanf("%d", &q);
		int a, b;
		for (int i = 0; i < q; i++) {
			scanf("%[^0-9]", ch);
			scanf("%d", &a);
			scanf("%[^0-9]", ch);
			scanf("%d", &b);
			ans[lca[a][b]]++;
		}
		scanf("%[^0-9]", ch);
		for (int i = 1; i <= n; i++) {
			if (ans[i]) printf("%d:%d\n", i, ans[i]);
		}
	}


	return 0;
}
