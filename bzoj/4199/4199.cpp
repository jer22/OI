#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
 
using namespace std;
 
const int MAXN = 300005;
const long long INF = 1000000000000000001ll;
 
int n;
int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1];
int siz[MAXN << 1];
long long val[MAXN << 1];
 
void extend(int c, int v) {
	int p = last;
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
	siz[np] = 1;
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
	val[last] = v;
}
int tp[MAXN << 1], c[MAXN];
vector<int> edges[MAXN << 1];
int arr[MAXN];
void build(char *str) {
	cnt = last = 1;
	n = strlen(str);
	for (int i = n - 1; i >= 0; i--)
		extend(str[i] - 'a', arr[i]);
	for (int i = 1; i <= cnt; i++) c[maxlen[i]]++;
	for (int i = 1; i <= n; i++) c[i] += c[i - 1];
	for (int i = cnt; i; i--) tp[c[maxlen[i]]--] = i;
	for (int i = cnt; i; --i) {
		int t = tp[i];
		siz[slink[t]] += siz[t];
		edges[slink[t]].push_back(t);
	}
}
 
long long sum[MAXN], mux[MAXN];
#define pll pair<long long, long long>
#define mp(i, j) make_pair((i), (j))
pll dfs(int x) {
	// cout << siz[x] << ' ' << maxlen[x] << ' ' << val[x] << endl;
 
	long long sons = 0;
	// long long fi = -INF, se = -INF;
	int si = edges[x].size();
	for (int i = 0; i < si; i++)
		sons += siz[edges[x][i]];
 
	long long mi = INF, mx = -INF;;
	if (siz[x] > sons) {
		mx = max(mx, val[x]);
		mi = min(mi, val[x]);
	}
	// if (maxlen[x] == 1) cout << "fff" << mx << ' ' << mi << endl;
	sons = 0;
	for (int i = 0; i < si; i++) {
		int nex = edges[x][i];
		pll t = dfs(nex);
 
		sum[maxlen[x]] += (long long)siz[nex] * sons;
		if (abs(t.first) != INF && abs(mx) != INF) mux[maxlen[x]] = max(mux[maxlen[x]], t.first * mx);
		if (abs(t.second) != INF && abs(mx) != INF) mux[maxlen[x]] = max(mux[maxlen[x]], t.second * mx);
		if (abs(t.first) != INF && abs(mi) != INF) mux[maxlen[x]] = max(mux[maxlen[x]], t.first * mi);
		if (abs(t.second) != INF && abs(mi) != INF) mux[maxlen[x]] = max(mux[maxlen[x]], t.second * mi);
		mi = min(mi, t.first);
		mx = max(mx, t.second);
		sons += siz[nex];
	}
	// if (val[x] > fi) se = fi, fi = val[x];
	// else if (val[x] > se) se = val[x];
	sum[maxlen[x]] += ((long long)siz[x] - sons) * sons;
	// mux[maxlen[x]] = max(mux[maxlen[x]], fi * se);
	return mp(mi, mx);
}
 
char str[MAXN];
int main() {
	freopen("4199.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", str);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	for (int i = 0; i <= n; i++)
		mux[i] = -INF;
	build(str);
	dfs(1);
	for (int i = n - 1; i >= 0; i--) {
		sum[i] += sum[i + 1];
		if (sum[i + 1]) mux[i] = max(mux[i], mux[i + 1]);
	}
	for (int i = 0; i < n; i++) {
		if (!sum[i]) mux[i] = 0;
		printf("%lld %lld\n", sum[i], mux[i]);
	}
 
	return 0;
}