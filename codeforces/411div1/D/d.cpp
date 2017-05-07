#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

const int MAXN = 100005;

int n, m, q;
vector<int> edges[MAXN];
int pfa[MAXN];

int findfa(int p) {
	if (p == pfa[p]) return p;
	return pfa[p] = findfa(pfa[p]);
}
void un(int a, int b) {
	pfa[findfa(a)] = findfa(b);
}
int vis[MAXN];
int col[MAXN];
int siz[MAXN];
int downmax[MAXN][2], maxson[MAXN];

void dfsdown(int x, int pre) {
	for (auto nex : edges[x]) if (nex != pre) {
		dfsdown(nex, x);
		if (downmax[nex][0] + 1 > downmax[x][0]) {
			downmax[x][1] = downmax[x][0];
			downmax[x][0] = downmax[nex][0] + 1;
			maxson[x] = nex;
		} else if (downmax[nex][0] + 1 > downmax[x][1]) {
			downmax[x][1] = downmax[nex][0] + 1;
		}
	}
}

int upmax[MAXN], mx[MAXN];
void dfsup(int x, int pre) {
	if (pre) {
		upmax[x] = upmax[pre] + 1;
		int idx = (maxson[pre] == x) ? 1 : 0;
		upmax[x] = max(upmax[x], downmax[pre][idx] + 1);
	}
	mx[x] = max(downmax[x][0], upmax[x]);
	for (auto nex : edges[x]) if (nex != pre) {
		dfsup(nex, x);
	}
}

int dia[MAXN];
vector<int> dist[MAXN];
map<pii, double> ans;

int getid(int i, int x) {
	int l = 0, r = dist[i].size() - 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (dist[i][mid] > x) r = mid;
		else l = mid + 1;
	}
	return l;
}

vector<long long> suf[MAXN];
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= n; i++)
		pfa[i] = i;
	for (int i = 0, a, b; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
		un(a, b);
	}
	int totc = 0;
	for (int i = 1; i <= n; i++) {
		int x = findfa(i);
		if (!vis[x]) {
			vis[x] = ++totc;
		}
		col[i] = vis[x];
		siz[col[i]]++;
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		if (!vis[col[i]]) {
			dfsdown(i, 0);
			dfsup(i, 0);
			vis[col[i]] = 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		dist[col[i]].push_back(mx[i]);
		dia[col[i]] = max(dia[col[i]], mx[i]);
	}
	for (int i = 1; i <= totc; i++)
		sort(dist[i].begin(), dist[i].end());
	for (int i = 1; i <= totc; i++) {
		int siz = dist[i].size();
		for (int j = siz; j >= 0; j--)
			suf[i].push_back(0);
		for (int j = siz - 1; j >= 0; j--)
			suf[i][j] = suf[i][j + 1] + dist[i][j];
	}

	ans.clear();
	for (int i = 0, a, b; i < q; i++) {
		scanf("%d %d", &a, &b);
		if (col[a] == col[b]) {
			printf("-1\n");
			continue;
		}
		if (siz[col[a]] > siz[col[b]]) swap(a, b);
		long long siz = dist[col[a]].size();
		long long sizb = dist[col[b]].size();
		if (ans.find({col[a], col[b]}) != ans.end()) {
			printf("%.10lf\n", ans[{col[a], col[b]}]);
			continue;
		}
		double p = 0.;
		int d = max(dia[col[a]], dia[col[b]]);
		for (int i = 0; i < siz; i++) {
			int x = dist[col[a]][i];
			int idx = getid(col[b], d - x - 1);
			if (dist[col[b]][idx] <= d - x - 1) idx++;
			p += (double)idx * d + (double)(x + 1) * (sizb - idx) + (double)suf[col[b]][idx];
		}
		ans[{col[a], col[b]}] = p / (siz * sizb);
		printf("%.10lf\n", ans[{col[a], col[b]}]);
	}


	return 0;
}
