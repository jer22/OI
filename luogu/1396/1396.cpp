#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXV 10010
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
	int to, v;
};

int V, E, S, T;
vector<Edge> edges[MAXV];
void addEdge(int x, int y, int z) {
	Edge e;
	e.v = z;
	e.to = y;
	edges[x].push_back(e);
	e.to = x;
	edges[y].push_back(e);
}

int dist[MAXV];
int done[MAXV];
void spfa() {
	queue<int> q;
	for (int i = 1; i <= V; i++)
		dist[i] = INF;
	memset(done, 0, sizeof(done));
	dist[S] = 0;
	q.push(S);
	done[S] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (max(dist[current], e.v) < dist[e.to]) {
				dist[e.to] = max(dist[current], e.v);
				if (!done[e.to]) {
					done[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		done[current] = 0;
	}
}

int main() {
	freopen("1396.in", "r", stdin);
	scanf("%d %d %d %d", &V, &E, &S, &T);
	int x, y, z;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &x, &y, &z);
		addEdge(x, y, z);
	}
	spfa();
	printf("%d\n", dist[T]);

	return 0;
}
