#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXV 2010
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
	int to, v;
};

int V;
vector<Edge> edges[MAXV];
void addEdge(int from, int to, int value) {
	Edge e;
	e.v = value;
	e.to = to;
	edges[from].push_back(e);
}

int dist[MAXV];
int done[MAXV];
void spfa() {
	queue<int> q;
	for (int i = 1; i <= V; i++) {
		dist[i] = 0;
	}
	dist[1] = INF;
	memset(done, 0, sizeof(done));
	q.push(1);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (min(e.v, dist[current]) > dist[e.to]) {
				dist[e.to] = min(e.v, dist[current]);
				if (!done[e.to]) {
					q.push(e.to);
					done[e.to] = 1;
				}
			}
		}
		done[current] = 0;
	}
}

int main() {
	freopen("p1391.in", "r", stdin);
	scanf("%d", &V);
	int x, y, z;
	while (true) {
		scanf("%d %d %d", &x, &y, &z);
		if (!x && !y && !z) break;
		addEdge(x, y, z);
	}
	spfa();
	for (int i = 2; i <= V; i++) {
		printf("%d\n", dist[i]);
	}

	return 0;
}
