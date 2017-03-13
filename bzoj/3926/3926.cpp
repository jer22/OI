#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int cnt, last;
int tr[MAXN << 5][26], maxlen[MAXN << 5], slink[MAXN << 5];

int extend(int p, int c) {
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
	while (!tr[p][c] && p) tr[p][c] = np, p = slink[p];
	if (!p) slink[np] = 1;
	else {
		int q = tr[p][c];
		if (maxlen[p] + 1 == maxlen[q]) slink[np] = q;
		else {
			int nq = ++cnt;
			maxlen[nq] = maxlen[p] + 1;
			memcpy(tr[nq], tr[q], sizeof(tr[q]));
			slink[nq] = slink[q];
			slink[np] = slink[q] = nq;
			while (tr[p][c] == q) tr[p][c] = nq, p = slink[p];
		}
	}
	return np;
}
int n, c;
int col[MAXN];
vector<int> edges[MAXN];
int deg[MAXN];

void dfs(int x, int pre, int p) {
	int np = extend(p, col[x]);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != pre) dfs(nex, x, np);
	}
}

int main() {
	freopen("3926.in", "r", stdin);
	scanf("%d %d", &n, &c);
	for (int i = 1; i <= n; i++)
		scanf("%d", &col[i]);
	cnt = 1;
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		deg[a]++, deg[b]++;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		if (deg[i] == 1) dfs(i, 0, 1);
	}
	long long ans = 0;
	for (int i = 1; i <= cnt; i++)
		ans += (long long)maxlen[i] - maxlen[slink[i]];
	printf("%lld\n", ans);
	return 0;
}
