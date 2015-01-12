#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define T (n + 1)
#define INF 0x3f3f3f3f

using namespace std;

int n, m;
int pig[1005];
int last[1005];
int edges[105][105];
int layer[105];

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(0);
	layer[0] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i <= T; i++) {
			if (layer[i] == -1 && edges[cur][i]) {
				layer[i] = layer[cur] + 1;
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
			int flow = find(i, min(temp, edges[v][i]));
			edges[v][i] -= flow;
			edges[i][v] += flow;
			temp -= flow;
		}
	}
	return cur - temp;
}

int dinic() {
	int flow, ans = 0;
	while (build()) {
		while (flow = find(0, INF))
			ans += flow;
	}
	return ans;
}

int main() {
	while (~scanf("%d %d", &m, &n)) {
		for (int i = 1; i <= m; i++)
			scanf("%d", &pig[i]);
		memset(last, 0, sizeof(last));
		memset(edges, 0, sizeof(edges));
		int k, a;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &k);
			for (int j = 1; j <= k; j++) {
				scanf("%d", &a);
				if (!last[a])
					edges[0][i] += pig[a];
				else edges[last[a]][i] = INF;
				last[a] = i;
			}
			scanf("%d", &edges[i][n + 1]);
		}
		int ans = dinic();
		cout << ans << endl;
	}
	return 0;
}
