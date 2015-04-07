#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define P(i, j) (((i) - 1) * m + (j))
#define T n * m + 1

using namespace std;

struct Edge{ int from, to, cap, flow; };
int n, m;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<Edge> edges;
vector<int> G[10005];

void addEdge(int from, int to, int cap) {
	edges.push_back((Edge){from, to, cap, 0});
	edges.push_back((Edge){to, from, 0, 0});
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

int layer[10005], cur[10005];

bool build() {
	queue<int> q;
	memset(layer, -1, sizeof(layer));
	q.push(0);
	layer[0] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < G[cur].size(); i++) {
			Edge e = edges[G[cur][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[cur] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int a) {
	if (x == T || !a) return a;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to] && (f = find(e.to, min(a, e.cap - e.flow)))) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(0, INF);
	}
	return ans;
}

int main() {
	freopen("1324.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int t, tot = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &t);
			tot += t;
			if ((i + j) & 1) {
				addEdge(0, P(i, j), t);
				for (int k = 0; k < 4; k++) {
					int nx = i + dir[k][0], ny = j + dir[k][1];
					if (nx >= 1 && nx <= n && ny >= 1 && ny <= m)
						addEdge(P(i, j), P(nx, ny), INF);
				}
			} else addEdge(P(i, j), T, t);
		}
	}
	tot -= dinic();
	printf("%d\n", tot);
	return 0;
}
