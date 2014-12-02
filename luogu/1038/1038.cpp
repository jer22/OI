#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge{
	int v;
	int to;
};

int V, E;
vector<Edge> e[1010];
int c[102];
int u[102];

int main( void ) {
	freopen("1038.in", "r", stdin);
	scanf("%d %d", &V, &E);
	for (int i = 1; i <= V; i++) {
		scanf("%d %d", &c[i], &u[i]);
		if (!c[i])
			c[i] -= u[i];
	}
	for (int i = 1; i <= E; i++) {
		int v, u, l;
		scanf("%d %d %d", &v, &u, &l);
		Edge temp;
		temp.v = l;
		temp.to = u;
		e[v].push_back(temp);
	}

	for (int i = 1; i <= V; i++) {
		if (c[i] <= 0) {
			continue;
		}
		for (int j = 0; j < e[i].size(); j++) {
			Edge &t = e[i][j];
			c[t.to] += t.v * c[i];
		}
	}
	int cnt = 0;
	for (int i = 1; i <= V; i++) {
		if (!e[i].size() && c[i] > 0) {
			cnt++;
			printf("%d %d\n", i, c[i]);
		}
	}
	if (!cnt) {
		printf("NULL\n");
	}
	return 0;
}
