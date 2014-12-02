#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

#define INF 0x3f3f3f3f
#define MAXN 110
#define T ((n << 1) + 1)

using namespace std;

struct Edge {
	int from, to, cap, flow;
};

int Q;
int n;
// int edges[MAXN][MAXN];
vector<Edge> edges;
vector<int> G[MAXN];
int atschool[MAXN];
int gohome[MAXN];
int layer[MAXN];

void addEdge(int from, int to, int cap) {
	Edge temp;
	temp.from = from;
	temp.to = to;
	temp.cap = cap;
	temp.flow = 0;
	edges.push_back(temp);
	temp.from = to;
	temp.to = from;
	temp.cap = 0;
	temp.flow = 0;
	edges.push_back(temp);
	int E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
}

bool build() {
	queue<int> q;
	memset(layer, -1, sizeof(layer));
	layer[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < G[v].size(); i++) {
			Edge &e = edges[G[v][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[v] + 1;
				q.push(e.to);
			}
		}
		// for (int i = 0; i <= T; i++) {
		// 	if (layer[i] == -1 && edges[v][i]) {
		// 		layer[i] = layer[v] + 1;
		// 		q.push(i);
		// 	}
		// }
	}
	return layer[T] != -1;
}

int find(int v, int cur) {
	if (v == T || !cur) return cur;
	int flow = 0;
	int f;
	for (int i = 0; i < G[v].size(); i++) {
		Edge &e = edges[G[v][i]];
		if (layer[v] + 1 == layer[e.to]
			&& (f = find(e.to, min(e.cap - e.flow, cur))) != 0) {
			e.flow += f;
			edges[G[v][i] + 1].flow -= f;
			flow += f;
			cur -= f;
			if (!cur) break;
		}
	}
	// for (int i = 0; i <= T; i++) {
	// 	if (edges[v][i] && layer[i] == layer[v] + 1) {
	// 		int flow = find(i, min(temp, edges[v][i]));
	// 		edges[v][i] -= flow;
	// 		edges[i][v] += flow;
	// 		temp -= flow;
	// 	}
	// }
	// return cur - temp;
	return flow;
}

int dinic() {
	int cur, ans = 0;
	while (build())
		// while (cur = find(0, INF))
		// 	ans += cur;
		ans += find(0, INF);
	return ans;
}

int main() {
	freopen("2055.in", "r", stdin);
	scanf("%d", &Q);
	while (Q--) {
		edges.clear();
		for (int i = 0; i <= T; i++) {
			G[i].clear();
		}
		// memset(edges, 0, sizeof(edges));
		memset(atschool, 0, sizeof(atschool));
		memset(gohome, 0, sizeof(gohome));
		int needBed = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &atschool[i]);
			if (atschool[i]) addEdge(i + n, T, 1);
				//edges[i + n][T] = 1;
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &gohome[i]);
			if (!atschool[i] || (atschool[i] && !gohome[i])) {
				addEdge(0, i, 1);
				// edges[0][i] = 1;
				needBed++;
			}
		}
		int t;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &t);
				if ((t || i == j) && (atschool[i] || atschool[j])) {
					addEdge(i, j + n, 1);
					// edges[i][j + n] = 1;
				}
			}
		}

		if (dinic() == needBed)
			printf("%c%c%c\n", 94, 95, 94);
		else printf("%c%c%c\n", 84, 95, 84);
	}


	return 0;
}
