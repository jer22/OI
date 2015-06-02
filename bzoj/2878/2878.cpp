#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to;
	double v;
	Edge() {}
	Edge(int a, double b) : to(a), v(b) {}
};

vector<Edge> edges[MAXN];
int n, m;
int vis[MAXN], flag;
double son[MAXN], fa[MAXN], up[MAXN], down[MAXN];
int cir[MAXN], tot, hash[MAXN];
int pre[MAXN], nex[MAXN];
double len[25][25];

void findCircle(int x, int f) {
	vis[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == f) continue;
		if (vis[e.to]) {
			flag = e.to;
			return;
		}
		findCircle(e.to, x);
		if (flag > 0) {
			if (flag == x) flag = -1;
			return;
		}
		if (flag == -1) break;
	}
	vis[x] = 0;
}

void dfs_cir(int x, int f) {
	if (hash[x]) return;
	cir[++tot] = x;
	hash[x] = tot;
	fa[x] = 2;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == f) continue;
		if (!vis[e.to]) continue;

		pre[e.to] = x;
		nex[x] = e.to;
		dfs_cir(e.to, x);
		len[hash[x]][hash[e.to]] = len[hash[e.to]][hash[x]] = e.v;
		break;
	}
}

void dfsdown(int x, int f) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (!vis[e.to] && e.to != f) {
			fa[e.to] = 1;
			dfsdown(e.to, x);
			son[x]++;
			down[x] += down[e.to] + e.v;
		}
	}
	if (son[x]) down[x] /= son[x];
}

void dfsup(int x, int f, double ee) {
	up[x] = ee;
	if (fa[f] + son[f] > 1) up[x] += (fa[f] * up[f] + son[f] * down[f] - down[x] - ee) / (fa[f] + son[f] - 1);
	for (int i = 0; i < edges[x].size(); i++)
		if (edges[x][i].to != f) dfsup(edges[x][i].to, x, edges[x][i].v);
}

int main() {
	scanf("%d %d", &n, &m);
	int a, b;
	double c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %lf", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	findCircle(1, 0);
	if (m < n) {
		dfsdown(1, 0);
		for (int i = 0; i < edges[1].size(); i++)
			dfsup(edges[1][i].to, 1, edges[1][i].v);
	} else {
		for (int i = 1; i <= n; i++) {
			if (vis[i]) {
				dfs_cir(i, 0);
				break;
			}
		}
		for (int i = 1; i <= tot; i++)
			dfsdown(cir[i], 0);
		for (int i = 1; i <= tot; i++) {
			int u = cir[i];
			double k = 1;
			for (int j = nex[u]; j != u; j = nex[j]) {
				if (nex[j] != u) up[u] += k * (len[hash[pre[j]]][hash[j]] + down[j] * son[j] / (son[j] + 1));
				else up[u] += k * (len[hash[pre[j]]][hash[j]] + down[j]);
				k /= (son[j] + 1);
			}
			k = 1;
			for (int j = pre[u]; j != u; j = pre[j]) {
				double z = up[j];
				if (pre[j] != u) up[u] += k * (len[hash[nex[j]]][hash[j]] + down[j] * son[j] / (son[j] + 1));
				else up[u] += k * (len[hash[nex[j]]][hash[j]] + down[j]);
				k /= (son[j] + 1);
			}
			up[u] /= 2;
		}
		for (int i = 1; i <= tot; i++) {
			for (int j = 0; j < edges[cir[i]].size(); j++) {
				Edge e = edges[cir[i]][j];
				if (!hash[e.to]) dfsup(e.to, cir[i], e.v);
			}
		}
	}

	double ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += (up[i] * fa[i] + down[i] * son[i]) / (fa[i] + son[i]);
	}
	printf("%.5lf\n", ans / n);
	return 0;
}
