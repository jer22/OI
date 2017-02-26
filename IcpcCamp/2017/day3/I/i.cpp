#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;

int n, q;
vector<int> edges[MAXN];

int fa[MAXN][22];
int maxlen[MAXN][3], leaf[MAXN][3];
int son[MAXN][3];
int longestchain[MAXN][2];
int po[MAXN][2], deep[MAXN];
int up[MAXN], upleaf[MAXN];
int upchain[MAXN][2], uppo[MAXN][2];

int getfa(int x, int d) {
	int p = x;
	for (int i = 0; i <= 18; i++)
		if ((1 << i) & d) p = fa[p][i];
	return p;
}

int getlca(int x, int y) {
	if (deep[x] > deep[y]) swap(x, y);
	int a = x, b = y;
	int t = deep[b] - deep[a];
	// for (int i = 0; i <= 18; i++)
	// 	if ((1 << i) & t) b = fa[b][i];
	b = getfa(b, t);
	for (int i = 18; i >= 0; i--)
		if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
	if (a != b) a = fa[a][0];
	return a;
}

int dist(int x, int y) {
	int lca = getlca(x, y);
	return deep[x] - deep[lca] + deep[y] - deep[lca];
}

void dfsup(int x, int pre) {
	up[x] = 0;
	upleaf[x] = x;
	upchain[x][0] = upchain[x][1] = 0;
	uppo[x][0] = uppo[x][1] = pre;
	if (x != 1) {
		up[x] = up[pre] + 1;
		upleaf[x] = upleaf[pre];

		int d = (son[pre][0] == x);
		int dd = d + 1 + int(son[pre][d + 1] == x);

		if (maxlen[pre][d] + 1 > up[x]) {
			up[x] = maxlen[pre][d] + 1;
			upleaf[x] = leaf[pre][d];
		}
		upchain[x][1] = maxlen[pre][d] + up[pre];
		uppo[x][0] = leaf[pre][d], uppo[x][1] = upleaf[pre];
		if (maxlen[pre][dd] > up[pre]) {
			upchain[x][1] = maxlen[pre][d] + maxlen[pre][dd];
			uppo[x][1] = leaf[pre][dd];
		}
		for (auto bro : edges[pre]) if (bro != x && bro != fa[pre][0]) {
			// if (x == 5) cout << bro << endl;
			int t = max(longestchain[bro][0], longestchain[bro][1]);
			if (t > upchain[x][0]) {
				upchain[x][0] = t;
				if (upchain[x][0] > upchain[x][1]) 
					uppo[x][0] = po[bro][0], uppo[x][1] = po[bro][1];
			}
		}
		int t = max(upchain[pre][0], upchain[pre][1]);
		if (t > upchain[x][0]) {
			upchain[x][0] = t;
			if (upchain[x][0] > upchain[x][1])
				uppo[x][0] = uppo[pre][0], uppo[x][1] = uppo[pre][1];
		}
	}
	for (auto nex : edges[x]) if (nex != pre) {
		dfsup(nex, x);
	}
}

void dfs(int x, int pre) {
	maxlen[x][0] = maxlen[x][1] = maxlen[x][2] = 0;
	leaf[x][0] = leaf[x][1] = leaf[x][2] = x;
	son[x][0] = son[x][1] = son[x][2] = 0;
	longestchain[x][0] = longestchain[x][1] = 0;
	po[x][0] = po[x][1] = 0;
	deep[x] = deep[pre] + 1;
	fa[x][0] = pre;
	for (int i = 1; i <= 18; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (auto nex : edges[x]) if (nex != pre) {
		dfs(nex, x);

		if (maxlen[nex][0] + 1 > maxlen[x][0]) {
			maxlen[x][2] = maxlen[x][1], maxlen[x][1] = maxlen[x][0], maxlen[x][0] = maxlen[nex][0] + 1;
			son[x][2] = son[x][1], son[x][1] = son[x][0], son[x][0] = nex;
			leaf[x][2] = leaf[x][1], leaf[x][1] = leaf[x][0], leaf[x][0] = leaf[nex][0];
		} else if (maxlen[nex][0] + 1 > maxlen[x][1]) {
			maxlen[x][2] = maxlen[x][1], maxlen[x][1] = maxlen[nex][0] + 1;
			son[x][2] = son[x][1], son[x][1] = nex;
			leaf[x][2] = leaf[x][1], leaf[x][1] = leaf[nex][0];
		} else if (maxlen[nex][0] + 1 > maxlen[x][2]) {
			maxlen[x][2] = maxlen[nex][0] + 1;
			son[x][2] = nex;
			leaf[x][2] = leaf[nex][0];
		}

	}
	longestchain[x][1] = maxlen[x][0] + maxlen[x][1];
	po[x][0] = leaf[x][0], po[x][1] = leaf[x][1];
	for (auto nex : edges[x]) if (nex != pre) {
		if (longestchain[nex][0] > longestchain[x][0]) {
			longestchain[x][0] = longestchain[nex][0];
			if (longestchain[x][0] > longestchain[x][1])
				po[x][0] = po[nex][0], po[x][1] = po[nex][1];
		}
		if (longestchain[nex][1] > longestchain[x][0]) {
			longestchain[x][0] = longestchain[nex][1];
			if (longestchain[x][0] > longestchain[x][1])
				po[x][0] = po[nex][0], po[x][1] = po[nex][1];
		}
	}
}

int fuck(int a, int b, int k, int d) {
	int lca = getlca(a, b);
	int kk = k + 1 >> 1;
	int dis;
	if (kk < deep[a] - deep[lca]) {
		int x = getfa(a, kk);
		// cout << x << endl;
		// cout << uppo[x][0] << ' ' << uppo[x][1] << endl;
		dis = max(dist(b, uppo[x][0]), dist(b, uppo[x][1]));
	} else {
		int x = getfa(b, d - kk - 1);
		dis = max(dist(b, po[x][0]), dist(b, po[x][1]));
	}
	return dis >= k - kk;
}

int main() {
	freopen("i.in", "r", stdin);
	// freopen("i.out", "w", stdout);
	while (~scanf("%d %d", &n, &q)) {
		int a, b, k;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		dfs(1, 0);
		dfsup(1, 0);
		// cout << uppo[2][0];
		while (q--) {
			scanf("%d %d %d", &a, &b, &k);
			int d = dist(a, b);
			if (d > k) printf("%d\n", k & 1);
			else {
				if (d & 1) {
					if (k & 1) {
						int l = k + 1 >> 1;
						if (l >= d) printf("2\n");
						else {
							printf("%d\n", (fuck(a, b, k, d) ^ 1) + 1);
						}
					} else {
						printf("0\n");
					}
				} else {
					if (k & 1) {
						printf("1\n");
					} else {
						int l = k >> 1;
						if (l >= d) printf("-1\n");
						else {
							printf("%d\n", fuck(b, a, k, d) - 1);
						}
					}
				}
			}
		}
	}


	return 0;
}
