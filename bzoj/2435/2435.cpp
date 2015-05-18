#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000005;

long long read() {
	long long x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int n;
vector<Edge> edges[MAXN];
int siz[MAXN], fa[MAXN];
long long ans;
int stack[MAXN], top;

void bfs() {
	queue<int> q;
	q.push(1);
	stack[top++] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (fa[cur] == e.to) continue;
			fa[e.to] = cur;
			q.push(e.to);
			stack[top++] = e.to;
		}
	}
	while (top--) {
		siz[stack[top]]++;
		siz[fa[stack[top]]] += siz[stack[top]];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			Edge e = edges[i][j];
			if (e.to == fa[i]) continue;
			ans += e.v * abs(siz[e.to] * 2 - n);
		}
	}
}

int main() {
	freopen("2435.in", "r", stdin);
	n = read();
	int a, b, c;
	for (int i = 1; i < n; i++) {
		a = read();
		b = read();
		c = read();
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	bfs();

	printf("%lld\n", ans);
	return 0;
}
