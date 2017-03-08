#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, root;
vector<int> edges[MAXN];
string name[MAXN];
int siz[MAXN], maxson[MAXN], deep[MAXN];
vector<pair<int, int> > que[MAXN];
int ans[MAXN];

void dfspre(int x, int d) {
	siz[x] = 1;
	deep[x] = d;
	for (auto nex : edges[x]) {
		dfspre(nex, d + 1);
		siz[x] += siz[nex];
		if (siz[nex] > siz[maxson[x]])
			maxson[x] = nex;
	}
}

set<string> s[MAXN];
void fuck(int x, int ban) {
	s[deep[x]].insert(name[x]);
	for (auto nex : edges[x])
		if (nex != ban) fuck(nex, ban);
}

void werjlesj(int x) {
	s[deep[x]].clear();
	for (auto nex : edges[x])
		werjlesj(nex);
}

void dfs(int x, bool keep) {

	for (auto nex : edges[x])
		if (nex != maxson[x]) dfs(nex, 0);
	if (maxson[x]) dfs(maxson[x], 1);

	fuck(x, maxson[x]);
	for (auto q : que[x]) {
		ans[q.second] = s[deep[x] + (q.first)].size();
	}
	if (!keep) werjlesj(x);
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
		cin >> name[i];
		scanf("%d", &x);
		edges[x].push_back(i);
	}
	dfspre(0, 1);
	scanf("%d", &m);
	for (int i = 0, x, k; i < m; i++) {
		scanf("%d %d", &x, &k);
		que[x].push_back({k, i});
	}
	dfs(0, 0);
	for (int i = 0; i < m; i++)
		printf("%d\n", ans[i]);

	return 0;
}
