#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, k;
vector<Edge> edges[MAXN];
long long num[MAXN], up[MAXN], down[MAXN], dist[MAXN][2], d[MAXN];

void dfs_down(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		dfs_down(e.to, x);
		num[x] += num[e.to];
		if (num[e.to]) down[x] += down[e.to] + (long long)(e.v) * 2;
		
	}
}

void dfs_up(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		up[e.to] = up[x] + down[x] - down[e.to];
		if (!num[e.to]) up[e.to] += (long long)(e.v) * 2;
		dfs_up(e.to, x);
	}
}

void dfs_down_dist(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		dfs_down_dist(e.to, x);
		if (num[e.to]) {
			if (dist[e.to][0] + (long long)(e.v) > dist[x][0]) {
				dist[x][1] = dist[x][0];
				dist[x][0] = dist[e.to][0] + (long long)(e.v);
			} else if (dist[e.to][0] + (long long)(e.v) > dist[x][1])
				dist[x][1] = dist[e.to][0] + (long long)(e.v);
		}
	}
}

void dfs_up_dist(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		d[e.to] = max(d[e.to], d[x] + (long long)(e.v));
		if (dist[x][0] == dist[e.to][0] + (long long)(e.v)) d[e.to] = max(d[e.to], dist[x][1] + (long long)(e.v));
		else d[e.to] = max(d[e.to], dist[x][0] + (long long)(e.v));
		dfs_up_dist(e.to, x);
	}
}

int main() {
	freopen("3743.in", "r", stdin);
	scanf("%d %d", &n, &k);
	int a, b, c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	for (int i = 0; i < k; i++) {
		scanf("%d", &a);
		num[a]++;
	}
	dfs_down(1, 1);
	dfs_up(1, 1);
	dfs_down_dist(1, 1);
	dfs_up_dist(1, 1);
	for (int i = 1; i <= n; i++) {
		printf("%lld\n", up[i] + down[i] - max(dist[i][0], d[i]));
	}

	return 0;
}
