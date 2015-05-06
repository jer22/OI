#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int T, n, m, top;
vector<int> edges[MAXN];
priority_queue<int> q;
int ans[MAXN];
int deg[MAXN];

void init() {
	top = 0;
	for (int i = 1; i <= n; i++)
		edges[i].clear();
	while (!q.empty()) q.pop();
	memset(deg, 0, sizeof(deg));
}

void topo() {
	for (int i = 1; i <= n; i++)
		if (!deg[i]) q.push(i);
	while (!q.empty()) {
		int x = q.top();
		q.pop();
		ans[++top] = x;
		for (int i = 0; i < edges[x].size(); i++)
			if (!--deg[edges[x][i]]) q.push(edges[x][i]);
	}
}

int main() {
	freopen("4010.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		init();
		int x, y;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			edges[y].push_back(x);
			deg[x]++;
		}
		topo();
		if (top != n) printf("Impossible!\n");
		else {
			for (int i = n; i >= 1; i--) {
				printf("%d ", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
