/*
ID:shijiey1
PROG:ditch
LANG:C++
*/

/*
裸的最小割，跑一遍最大流。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXV 205
#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int from, to, cap, flow;
};

vector<int> G[MAXV];
vector<Edge> edges;
void addEdge(int from, int to, int cap) {
	Edge e;
	e.from = from;
	e.to = to;
	e.cap = cap;
	e.flow = 0;
	edges.push_back(e);
	e.from = to;
	e.to = from;
	e.cap = 0;
	edges.push_back(e);
	int E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
}

int V, E;
int cur[MAXV];
int layer[MAXV];
int done[MAXV];
bool build() {
	memset(layer, -1, sizeof(layer));
	memset(done, 0, sizeof(done));
	layer[1] = 0;
	done[1] = 1;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge e = edges[G[x][i]];
			if (!done[e.to] && e.cap > e.flow) {
				done[e.to] = 1;
				q.push(e.to);
				layer[e.to] = layer[x] + 1;
			}
		}
	}
	return done[V];
}

int find(int x, int a) {
	if (x == V || !a) return a;
	int flow = 0;
	int f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(e.cap - e.flow, a))) != 0) {
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
		ans += find(1, INF);
	}
	return ans;
}

int main() {
	freopen("ditch.in", "r", stdin);
	freopen("ditch.out", "w", stdout);
	scanf("%d %d", &E, &V);
	int a, b, c;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		addEdge(a, b, c);
	}
	int ans = dinic();
	printf("%d\n", ans);
	return 0;
}
