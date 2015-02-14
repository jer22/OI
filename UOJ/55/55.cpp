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

int T, n;
vector<Edge> edges[100005];
int r[100005];
int lastans = 0;
int now;
inline void dfs(int cur, int pre, int dist) {
	if (r[cur] + r[now] >= dist && cur != 0) lastans++;
	for (int i = 0; i < edges[cur].size(); i++) {
		Edge e = edges[cur][i];
		if (e.to == pre) continue;
		dfs(e.to, cur, dist + e.v);
	}
}

int main() {
	freopen("55.in", "r", stdin);
	scanf("%d %d", &T, &n);
	// if (T <= 4) {
		int a, b, c;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			a  = a ^ (lastans % 1000000000);
			now = i;
			edges[i].push_back(Edge(a, b));
			edges[a].push_back(Edge(i, b));
			r[i] = c;
			dfs(a, i, b);
			cout << lastans << endl;
		}
	// }


	return 0;
}
