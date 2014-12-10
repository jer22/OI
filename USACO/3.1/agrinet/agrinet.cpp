/*
ID:shijiey1
PROG:agrinet
LANG:C++
*/

/*
裸的最小生成树
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Edge{
	int from, to, value;
	bool operator < (const Edge &e) const {
		return value < e.value;
	}
};

int n;
Edge edges[10010];
int parent[110];
int cnt = 0;

int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

void un(int p, int q) {
	parent[find(p)] = find(q);
}

int main() {
	freopen("agrinet.in", "r", stdin);
	freopen("agrinet.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
	int t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &t);
			if (i < j) {
				Edge e;
				e.from = i;
				e.to = j;
				e.value = t;
				edges[cnt++] = e;
			}
		}
	}
	sort(edges, edges + cnt);
	int ans = 0;
	for (int i = 0; i < cnt; i++) {
		Edge e = edges[i];
		if (find(e.from) != find(e.to)) {
			ans += e.value;
			un(e.from, e.to);
		}
	}
	printf("%d\n", ans);

	return 0;
}
