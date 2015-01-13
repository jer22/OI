#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define T (n + 1)

using namespace std;

struct Edge{
	int from, to, cap, flow;
	Edge() {}
	Edge(int a, int b, int c, int d) : from(a), to(b), cap(c), flow(d) {}
};

int cas;
int n, m;
int in[205], out[205];
int cnt[205][205];
vector<Edge> edges;
vector<int> G[205];
void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(from, to, cap, 0));
	edges.push_back(Edge(to, from, 0, 0));
	int siz = edges.size();
	G[from].push_back(siz - 2);
	G[to].push_back(siz - 1);
}

void buildGraph() {
	for (int i = 1; i <= n; i++) {
		if (in[i] > out[i]) addEdge(0, i, (in[i] - out[i]) >> 1);
		if (out[i] > in[i]) addEdge(i, T, (out[i] - in[i]) >> 1);
		for (int j = 1; j <= n; j++)
			if (cnt[i][j]) addEdge(j, i, cnt[i][j]);
	}
}

int cur[205];
int layer[205];
bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(0);
	layer[0] = 0;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge e = edges[G[current][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[current] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int curflow) {
	if (x == T || !curflow) return curflow;
	int f, flow = 0;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[e.to] == layer[x] + 1
			&& (f = find(e.to, min(curflow, e.cap - e.flow)))) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			curflow -= f;
			if (!curflow) break;
		}
	}
	return flow;
}

int dinic() {
	int maxflow = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		maxflow += find(0, INF);
	}
	return maxflow;
}

int main() {
	freopen("1637.in", "r", stdin);
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d %d", &n, &m);
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i <= n; i++)
			G[i].clear();
		edges.clear();
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			in[b]++;
			out[a]++;
			if (!c) cnt[a][b]++;
		}
		int flow = 0;
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			if (in[i] > out[i])
				flow += (in[i] - out[i] >> 1);
			if (abs(in[i] - out[i]) & 1) {
				flag = false;
				break;
			}
		}
		if (!flag) {
			printf("impossible\n");
			continue;
		}
		buildGraph();
		int maxflow = dinic();
		if (maxflow == flow) printf("possible\n");
		else printf("impossible\n");
	}
	return 0;
}
