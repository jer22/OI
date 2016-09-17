#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int T, n;
vector<Edge> edges[MAXN];
int maxson[MAXN], maxlen[MAXN], siz[MAXN];
int seclen[MAXN];
int pre[MAXN], prelen[MAXN];

int root1, root2, dsiz;
long long dlen;



void dfsroot(int x, int fa) {
	maxson[x] = 0;
	maxlen[x] = 0;
	// secson[x] = x;
	seclen[x] = 0;

	// pre[x] = 0;
	prelen[x] = 0;
	siz[x] = 0;


	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == fa) continue;
		dfsroot(e.to, x);
		if (maxlen[e.to] + e.v > maxlen[x] || pre[e.to] == x) {

			seclen[x] = maxlen[x];

			pre[e.to] = x;
			prelen[e.to] = e.v;
			maxlen[x] = maxlen[e.to] + e.v;
			maxson[x] = e.to;
			siz[x] = siz[e.to] + 1;

		} else if (maxlen[e.to] + e.v > seclen[x]) {
			seclen[x] = maxlen[e.to] + e.v;

		}
	}
}

long long ret[MAXN];

long long dfsans1(int x) {
	if (!maxson[x]) return prelen[x];
	long long now = dfsans1(maxson[x]);
	if (x != root1)  {
		
		ret[x] = now + seclen[x];
	}
	return now + prelen[x];
}

long long dfsans2(int x) {
	if (!maxson[x]) return prelen[x];
	long long now = dfsans2(maxson[x]);
	if (x != root2)  {
		
		ret[pre[x]] = max(ret[pre[x]], now + seclen[x]);
	}
	return now + prelen[x];
}

int main() {
	freopen("1009.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int a, b, c;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		for (int i = 1; i <= n; i++)
			pre[i] = 0;
		dfsroot(1, 1);
		root1 = 1;
		while (maxson[root1]) root1 = maxson[root1];
		for (int i = 1; i <= n; i++)
			pre[i] = 0;
		dfsroot(root1, root1);
		root2 = root1;
		while (maxson[root2]) root2 = maxson[root2];
		dsiz = siz[root1];
		dlen = maxlen[root1];

		long long ans = (long long)(n - 1 - dsiz) * dlen;

		memset(ret, 0, sizeof(ret));
		dfsans1(root1);

		dfsroot(root2, root2);
		dfsans2(root2);

		for (int i = 1; i <= n; i++) {
			ans += ret[i];
			// cout << ret[i] << ' ';
		}
		// cout << endl;

		printf("%lld\n", ans);

	}

	return 0;
}
