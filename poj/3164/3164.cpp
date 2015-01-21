#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

#define MAXN 110

using namespace std;

const double INF = 1000000000;

struct Point{
	double x, y;
};

struct Edge{
	int from, to;
	double v;
};

int n, m;
Point points[MAXN];
Edge edges[MAXN * MAXN];
int vis[MAXN];
int color[MAXN];
double in[MAXN];
int pre[MAXN];
double getDist(int a, int b) {
	if (a == b) return INF;
	return sqrt((points[a].x - points[b].x) * (points[a].x - points[b].x)
		+ (points[a].y - points[b].y) * (points[a].y - points[b].y));
}

double solve() {
	double ans = 0;
	int V = n, E = m;
	int root = 1;
	while (true) {
		for (int i = 1; i <= V; i++)
			in[i] = INF;
		for (int i = 0; i < E; i++) {
			if (edges[i].from == edges[i].to) continue;
			if (edges[i].v < in[edges[i].to]) {
				pre[edges[i].to] = edges[i].from;
				in[edges[i].to] = edges[i].v;
			}
		}
		for (int i = 1; i <= V; i++)
			if (in[i] == INF && i != root) return -1;
		int newNodes = 1;
		memset(color, -1, sizeof(color));
		memset(vis, -1, sizeof(vis));
		in[root] = 0;
		for (int i = 1; i <= V; i++) {
			ans += in[i];
			int v = i;
			while (vis[v] != i && color[v] == -1 && v != root) {
				vis[v] = i;
				v = pre[v];
			}
			if (v != root && color[v] == -1) {
				for (int t = pre[v]; t != v; t = pre[t]) {
					color[t] = newNodes;
				}
				color[v] = newNodes++;
			}
		}
		if (newNodes == 1) break;
		for (int i = 1; i <= V; i++)
			if (color[i] == -1)
				color[i] = newNodes++;
		for (int i = 0; i < E; i++) {
			int t = edges[i].to;
			edges[i].from = color[edges[i].from];
			edges[i].to = color[edges[i].to];
			if (edges[i].from != edges[i].to) {
				edges[i].v -= in[t];
			}
		}
		V = newNodes - 1;
		root = color[root];
	}
	return ans;
}

int main() {
	freopen("3164.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++)
			scanf("%lf %lf", &points[i].x, &points[i].y);
		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[i].from = a;
			edges[i].to = b;
			edges[i].v = getDist(a, b);
		}
		double ans = solve();
		if (ans == -1) printf("poor snoopy\n");
		else printf("%.2f\n", ans);
	}
	return 0;
}
