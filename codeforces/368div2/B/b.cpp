#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m, k;
vector<Edge> edges[100005];
int sto[100005];
int vis[100005];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> m >> k;
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	for (int i = 0; i < k; i++) {
		scanf("%d", &sto[i]);
		vis[sto[i]] = 1;
	}
	if (!k || k == n) {
		printf("-1\n");
		return 0;
	}
	int ans = 0x3f3f3f3f;
	for (int i = 0; i < k; i++) {
		int now = sto[i];
		for (int j = 0; j < edges[now].size(); j++) {
			Edge e = edges[now][j];
			if (!vis[e.to]) {
				ans = min(ans, e.v);
			}
		}
	}
	if (ans == 0x3f3f3f3f) ans = -1;
	printf("%d\n", ans);
	

	return 0;
}
