#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, q;
vector<int> edges[MAXN];
int siz[MAXN], son[MAXN], col[MAXN];
vector<pair<int, int> > que[MAXN];

void dfspre(int x, int pre) {
	siz[x] = 1;
	for (auto nex : edges[x]) if (nex != pre) {
		dfspre(nex, x);
		siz[x] += siz[nex];
		if (siz[nex] > siz[son[x]])
			son[x] = nex;
	}
}
int c[MAXN];

void insert(int p, int x) {
	for (int i = p; i; i -= i & -i)
		c[i] += x;
}
int getsum(int p) {
	int ans = 0;
	for (int i = p; i < MAXN; i += i & -i)
		ans += c[i];
	return ans;
}
int cnt[MAXN];
void fuck(int x, int pre, int ban) {
	if (cnt[col[x]]) insert(cnt[col[x]], -1);
	cnt[col[x]]++;
	insert(cnt[col[x]], 1);
	for (auto nex : edges[x])
		if (nex != pre && nex != ban) fuck(nex, x, ban);
}
void klasdjfl(int x, int pre) {
	insert(cnt[col[x]], -1);
	cnt[col[x]]--;
	if (cnt[col[x]]) insert(cnt[col[x]], 1);
	for (auto nex : edges[x])
		if (nex != pre) klasdjfl(nex, x);
}

int ans[MAXN];

void dfs(int x, int pre, bool keep) {
	for (auto nex : edges[x])
		if (nex != pre && nex != son[x]) dfs(nex, x, 0);
	if (son[x]) dfs(son[x], x, 1);
	fuck(x, pre, son[x]);
	for (auto q : que[x]) {
		ans[q.second] = getsum(q.first);
	}
	if (!keep) klasdjfl(x, pre);
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &col[i]);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfspre(1, 0);
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		que[a].push_back({b, i});
	}
	dfs(1, 0, 0);
	for (int i = 0; i < q; i++)
		printf("%d\n", ans[i]);

	return 0;
}