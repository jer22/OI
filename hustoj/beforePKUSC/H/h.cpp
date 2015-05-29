#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int T, n;
vector<Edge> edges[MAXN];
int siz[MAXN];
long long ans;

int top;
pair<int, int> q[MAXN * 2];

void dfs() {

	q[++top] = make_pair(1, 0);
	memset(siz, 0, sizeof(siz));
	while (top) {
		pair<int, int> u = q[top--];
		if (!siz[u.first]) {
			siz[u.first] = 1, q[++top] = u;
			for (int i = 0; i < edges[u.first].size(); i++) {
				int to = edges[u.first][i].to;
				if (to != u.second)
					q[++top] = make_pair(to, u.first);
			}
		}
		else {
			for (int i = 0; i < edges[u.first].size(); i++) {
				int to = edges[u.first][i].to;
				if (to != u.second) {
					ans += edges[u.first][i].v * min(siz[to], n - siz[to]);
					siz[u.first] += siz[to];
				}
			}
		}
	}
}

int main() {
	freopen("h.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int a, b;
		long long c;
		for (int i = 1; i < n; i++) {
			scanf("%d %d %lld", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		ans = 0, top = 0;
		dfs();
		printf("Case #%d: %lld\n", cas++, ans * 2);
	}


	return 0;
}
