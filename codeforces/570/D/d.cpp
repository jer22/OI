#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 500005;

int n, m;
vector<int> edges[MAXN];
vector<pii > query[MAXN];
int deep[MAXN] ,siz[MAXN], mxson[MAXN];
bool big[MAXN], ans[MAXN];
int cnt[MAXN][30], cntall[MAXN];
char str[MAXN];
void dfssize(int x) {
	siz[x] = 1;
	for (auto nex : edges[x]) {
		dfssize(nex);
		siz[x] += siz[nex];
		if (!mxson[x] || siz[nex] > siz[mxson[x]])
			mxson[x] = nex;
	}
}
void add(int x, int f) {
	cntall[deep[x]] -= cnt[deep[x]][str[x] - 'a'];
	cnt[deep[x]][str[x] - 'a'] ^= 1;
	cntall[deep[x]] += cnt[deep[x]][str[x] - 'a'];
	for (auto nex : edges[x])
		if (!big[nex]) add(nex, f);
}
void dfs(int x, bool keep) {
	for (auto nex : edges[x])
		if (nex != mxson[x]) dfs(nex, 0);
	big[mxson[x]] = 1;
	if (mxson[x]) dfs(mxson[x], 1);
	add(x, 1);
	for (auto q : query[x])
		ans[q.second] = (cntall[q.first] <= 1);
	big[mxson[x]] = 0;
	if (!keep) add(x, -1);
}
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d %d", &n, &m);
	deep[1] = 1;
	for (int i = 2, x; i <= n; i++) {
		scanf("%d", &x);
		edges[x].push_back(i);
		deep[i] = deep[x] + 1;
	}
	scanf("%s", str + 1);
	dfssize(1);
	for (int i = 1, a, b; i <= m; i++) {
		scanf("%d %d", &a, &b);
		query[a].push_back(mp(b, i));
	}
	dfs(1, 0);
	for (int i = 1; i <= m; i++)
		cout << (ans[i] ? "Yes\n" : "No\n");

	return 0;
}
