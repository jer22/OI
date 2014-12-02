#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define INF 0x3f3f3f3f
#define T ((n << 1) + 1)

using namespace std;

struct Edge{
	int to, v;
};

int Q;
int n, m;
int arr[60];
int edges[200][200];

int layer[200];
bool build() {
	queue<int> q;
	memset(layer, -1, sizeof(layer));
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
	if (v == T) return cur;
	int temp = cur;
	for (int i = 0; i <= T; i++) {
		if (edges[v][i] > 0 && layer[v] + 1 == layer[i]) {
			int flow = find(i, min(edges[v][i], temp));
			edges[v][i] -= flow;
			edges[i][v] += flow;
			temp -= flow;
		}
	}
	return cur - temp;
}

int dinic() {
	int cur, ans = 0;
	while (build())
		while (cur = find(0, INF))
			ans += cur;
	return ans;
}

int main() {
	freopen("input", "r", stdin);
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d %d", &n, &m);
		memset(edges, 0, sizeof(edges));
		memset(arr, 0, sizeof(arr));
		for (int i = 1; i <= n - 1; i++) {
			scanf("%d", &arr[i]);
			edges[i][i + n + 1] = arr[i];
		}
		edges[0][n + 1] = INF;
		edges[n][T] = INF;
		int x, y;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			edges[x + n + 1][y] = INF;
			edges[y + n + 1][x] = INF;
		}
		int ans = dinic();
		if (!ans)
			printf("Min!\n");
		else if (ans == INF)
			printf("Max!\n");
		else printf("%d\n", ans);
	}


	return 0;
}
