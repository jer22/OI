#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <stack>

using namespace std;

const double eps = 1e-8;
const int MAXN = 1005;

struct Node{
	double x, y, r;
	int cost;
	Node() {}
	Node(double a, double b, double c, int d)
	: x(a), y(b), r(c), cost(d) {}
};

int T, n;
Node arr[MAXN];
vector<int> edges[MAXN];
bool check(Node a, Node b) {
	double dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	if (fabs(dist - a.r * a.r) < eps) return true;
	return dist + eps < a.r * a.r;
}

int cnt, num;
int vis[MAXN], dfn[MAXN], low[MAXN], col[MAXN];
stack<int> st;
int dfs(int u) {
	st.push(u);
	vis[u] = 1;
	++cnt;
	low[u] = dfn[u] = cnt;
	for (int j = 0; j < edges[u].size(); j++) {
		int v = edges[u][j];
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		int t;
		num++;
		do {
			t = st.top();
			col[t] = num;
			st.pop();
			vis[t] = 0;
		}
		while (t != u);
	}
}

int mi[MAXN], ind[MAXN];
int main() {
	// freopen("5934.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf %lf %d", &arr[i].x, &arr[i].y, &arr[i].r, & arr[i].cost);
			for (int j = 1; j < i; j++) {
				if (check(arr[i], arr[j])) edges[i].push_back(j);
				if (check(arr[j], arr[i])) edges[j].push_back(i);
			}
		}
		cnt = num = 0;
		memset(vis, 0, sizeof(vis));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(col, 0, sizeof(col));
		memset(mi, 0x3f, sizeof(mi));
		memset(ind, 0, sizeof(ind));
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) dfs(i);
		for (int i = 1; i <= n; i++)
			mi[col[i]] = min(mi[col[i]], arr[i].cost);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				int v = edges[i][j];
				if (col[i] != col[v])
					ind[col[v]]++;
			}
		}
		int ans = 0;
		for (int i = 1; i <= num; i++)
			if (!ind[i]) ans += mi[i];
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}
