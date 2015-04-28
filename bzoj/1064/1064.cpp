#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m;
int ans1, ans2;
int mx, mi;
bool vis[MAXN];
vector<Edge> edges[MAXN];
int dist[MAXN];

int gcd(int a, int b) {
	if (!a && !b) return 0;
	if (a > b) swap(a, b);
	while (b ^= a ^= b ^= a %= b);
	return a;
}

void dfs1(int x) {
	vis[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (!vis[e.to]) {
			dist[e.to] = dist[x] + e.v;
			dfs1(e.to);
		} else ans1 = gcd(ans1, abs(dist[x] + e.v - dist[e.to]));
	}
}

void dfs2(int x) {
	vis[x] = 1;
	mx = max(mx, dist[x]);
	mi = min(mi, dist[x]);
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (!vis[e.to]) {
			dist[e.to] = dist[x] + e.v;
			dfs2(e.to);
		}
	}
}

int main() {
	freopen("1064.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(Edge(b, 1));
		edges[b].push_back(Edge(a, -1));
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) dfs1(i);
	if (ans1) for (ans2 = 3; ans2 < ans1 && ans1 % ans2; ans2++);
	else {
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				mx = mi = dist[i] = 0;
				dfs2(i);
				ans1 += mx - mi + 1;
			}
		}
		ans2 = 3;
	}
	if (ans1 < 3) ans1 = ans2 = -1;
	printf("%d %d\n", ans1, ans2);
	return 0;
}
