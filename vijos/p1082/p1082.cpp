#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXV 5010
#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int to, value, cost;
};

int V, E, S, T;
int maxHp;
vector<Edge> edges[MAXV];
void addEdge(int x, int y, int c, int d) {
	Edge e;
	e.value = d;
	e.cost = c;
	e.to = y;
	edges[x].push_back(e);
	e.to = x;
	edges[y].push_back(e);
}

int dist[MAXV];
int hp[MAXV];
int done[MAXV];
int spfa() {
	queue<int> q;
	for (int i = 1; i <= V; i++) {
		dist[i] = INF;
	}
	memset(hp, 0, sizeof(hp));
	memset(done, 0, sizeof(done));
	dist[S] = 0;
	done[S] = 1;
	q.push(S);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (dist[current] + e.value < dist[e.to] && hp[current] + e.cost <= maxHp) {
				dist[e.to] = dist[current] + e.value;
				hp[e.to] = hp[current] + e.cost;
				if (!done[e.to]) {
					done[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		done[current] = 0;
	}
	if (dist[T] != INF)
		return dist[T];
	return -1;
}

int main() {
	freopen("p1082.in", "r", stdin);
	scanf("%d %d", &V, &E);
	int x, y, c, d;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d %d", &x, &y, &c, &d);
		addEdge(x, y, c, d);
	}
	scanf("%d %d", &S, &T);
	scanf("%d", &maxHp);
	int ans = spfa();
	printf("%d\n", ans);

	return 0;
}
