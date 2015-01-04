#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[50005];
set<int> gift[50005];
bool vis[50005];
void addEdge(int a, int b) {
	edges[a].push_back(b);
}

void dfs(int i) {
	for (int j = 0; j < edges[i].size(); j++) {
		int nex = edges[i][j];
		if (vis[nex]) continue;
		vis[nex] = true;
		dfs(nex);
		for (set<int>::iterator it = gift[nex].begin(); it != gift[nex].end(); it++) {
			int t = *(it);
			gift[i].insert(t);
		}
		vis[nex] = false;
	}
}

int main() {
	freopen("1003.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			gift[i].clear();
		}
		int a, b;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			addEdge(a, b);
			addEdge(b, a);
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &a, &b);
			gift[a].insert(b);
		}
		memset(vis, 0, sizeof(vis));
		vis[1] = true;
		dfs(1);
		for (int i = 1; i <= n; i++) {
			if (i > 1) printf(" ");
			int t = gift[i].size();
			printf("%d", t);
		}
		printf("\n");
	}


	return 0;
}
