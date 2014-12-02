#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

#define INF 0x3f3f3f3f
#define T 699

using namespace std;

int n, m;
int a[210];
int b[210];
int edges[800][800];

bool canLink(int x, int y) {
	int z = x ^ y;
	int p = 32 - __builtin_clz(z);
	return ((1 << p) == (1 + z));
}

int layer[800];
bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	layer[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i <= T; i++) {
			if (edges[v][i] && layer[i] == -1) {
				layer[i] = layer[v] + 1;
				q.push(i);
			}
		}
	}
	return layer[T] != -1;
}

int find(int v, int cur) {
	int temp = cur;
	if (v == T) return cur;
	for (int i = 0; i <= T; i++) {
		if (edges[v][i] && layer[v] + 1 == layer[i]) {
			int flow = find(i, min(temp, edges[v][i]));
			edges[v][i] -= flow;
			edges[i][v] += flow;
			temp -= flow;
		}
	}
	return cur - temp;
}

int dinic() {
	int ans = 0, cur;
	while (build())
		while (cur = find(0, INF))
			ans += cur;
	return ans;
}

int main() {
	freopen("input", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (canLink(a[i], b[j])) {
				edges[i][j + 300] = 1;
				edges[0][i] = 1;
				edges[j + 300][T] = 1;
			}
		}
	}
	int ans = dinic();
	if (ans) {
		printf("%d\n", ans);
	} else {
		printf("I want nobody nobody but you\n");
	}
	

	return 0;
}
