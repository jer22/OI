#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int n, m;
int cnt[MAXN];
vector<int> col[MAXN];
vector<int> edges[MAXN];
int ans[MAXN];

set<int> vis;
void dfs(int x, int pre) {
	int idx = 1;
	vis.clear();
	for (auto c : col[x])
		if (ans[c]) vis.insert(ans[c]);
	for (auto c : col[x]) {
		if (ans[c])
			continue;
		while (vis.find(idx) != vis.end()) ++idx;
		ans[c] = idx;
		vis.insert(ans[c]);
	}

	for (auto nex : edges[x])
		if (nex != pre) dfs(nex, x);
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cnt[i]);
		for (int j = 0, x; j < cnt[i]; j++) {
			scanf("%d", &x);
			col[i].push_back(x);
		}
	}
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 0);
	int cc = 0;
	for (int i = 1; i <= m; i++) {
		if (!ans[i]) ans[i] = 1;
		cc = max(cc, ans[i]);
	}
	printf("%d\n", cc);
	for (int i = 1; i <= m; i++) {

		printf("%d%c", ans[i], " \n"[i == m]);
	}



	return 0;
}
