#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 100005;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int n, k;
long long dist[MAXN];
int cnt[MAXN];
bool vis[MAXN];
vector<Edge> edges[MAXN];
int q[MAXN];
long long spfa() {
	int h = 0, t = 0;
	q[t++] = 0;
	dist[0] = 0;
	vis[0] = cnt[0] = 1;
	while (h != t) {
		int cur = q[h++];
		if (h == MAXN) h = 0;
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (dist[cur] + e.v > dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
				if (++cnt[e.to] == n) return -1;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q[t++] = e.to;
					if (t == MAXN) t = 0;
				}
			}
		}
		vis[cur] = 0;
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += dist[i];
	}
	return ans;
}

int main() {
	freopen("2330.in", "r", stdin);
	scanf("%d %d", &n, &k);
	int x, a, b;
	for (int i = 0; i < k; i++) {
		scanf("%d %d %d", &x, &a, &b);
		if (x == 1) {
			edges[a].push_back(Edge(b, 0));
			edges[b].push_back(Edge(a, 0));
		} else if (x == 2) {
			if (a == b) {
				printf("-1\n");
				return 0;
			}
			edges[a].push_back(Edge(b, 1));
		} else if (x == 3) edges[b].push_back(Edge(a, 0));
		else if (x == 4) {
			if (a == b) {
				printf("-1\n");
				return 0;
			}
			edges[b].push_back(Edge(a, 1));
		} else edges[a].push_back(Edge(b, 0));
	}
	for (int i = 1; i <= n; i++) edges[0].push_back(Edge(i, 1));
	long long ans = spfa();
	printf("%lld\n", ans);
	return 0;
}
