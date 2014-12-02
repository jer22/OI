#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 10000;

int e[MAXV][MAXV];
int layer[MAXV];
int V, E;

int min(int a, int b) {
	return a < b ? a : b;
}

bool build() {
	queue<int> q;
	memset(layer, -1, sizeof(layer));
	layer[1] = 0;
	q.push(1);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 1; i <= V; i++) {
			if (layer[i] == -1 && e[v][i]) {
				layer[i] = layer[v] + 1;
				q.push(i);
			}
		}
	}
	return layer[V] != -1;
}

int find(int v, int cur) {
	int temp = cur;
	if (v == V) return cur;
	for (int i = 1; i <= V; i++) {
		if (e[v][i] > 0 && layer[v] + 1 == layer[i]) {
			int flow = find(i, min(temp, e[v][i]));
			e[v][i] -= flow;
			e[i][v] += flow;
			temp -= flow;
		}
	}
	return cur - temp;
}

int dinic() {
	int cur, ans = 0;
	while (build()) {
		while (cur = find(1, INF))
			ans += cur;
	}
	return ans;
}

int main( void ) {
	scanf("%d %d", &V, &E);
	int x, y, l;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &x, &y, &l);
		e[x][y] = l;
	}
	printf("%d\n", dinic());
	return 0;
}
