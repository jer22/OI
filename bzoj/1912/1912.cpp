#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;


int n, K;
struct Edge{ int v, w, next; } edges[200005];
int head[MAXN], cnt = 0;

void insert(int u, int v) {
	edges[cnt] = (Edge){v, 1, head[u]}, head[u] = cnt++;
}

int s, len;
int son1[MAXN], son2[MAXN];

int dfs(int x, int pre) {
	int fir = 0, sec = 0;
	for (int p = head[x]; p != -1; p = edges[p].next) {
		int v = edges[p].v;
		if (v == pre) continue;
		int now = dfs(v, x) + edges[p].w;
		if (now > fir) sec = fir, fir = now, son2[x] = son1[x], son1[x] = p;
		else if (now > sec) sec = now, son2[x] = p;
	}
	if (len < fir + sec) len = fir + sec, s = x;
	return fir;
}

int main() {
	freopen("1912.in", "r", stdin);
	scanf("%d %d", &n, &K);
	memset(head, -1, sizeof(head));
	int u, v;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		insert(u, v);
		insert(v, u);
	}
	memset(son1, -1, sizeof(son1));
	memset(son2, -1, sizeof(son2));
	int ans = n - 1 << 1;
	len = 0;
	dfs(1, -1);
	ans -= len - 1;
	if (K == 2) {
		len = 0;
		for (int i = son1[s]; i != -1; i = son1[edges[i].v])
			edges[i].w = edges[i ^ 1].w = -1;
		for (int i = son2[s]; i != -1; i = son1[edges[i].v])
			edges[i].w = edges[i ^ 1].w = -1;
		memset(son1, -1, sizeof(son1));
		memset(son2, -1, sizeof(son2));
		dfs(1, -1);
		ans -= len - 1;
	}
	printf("%d\n", ans);
	return 0;
}
