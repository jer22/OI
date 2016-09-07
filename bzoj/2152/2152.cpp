#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n;
vector<Edge> edges[MAXN];
bool cut[MAXN];

/***************************树的重心************************************/
int sz_down[MAXN];
void dfs(int x, int pre) {
	sz_down[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == pre) continue;
		if (cut[nex]) continue;
		dfs(nex, x);
		sz_down[x] += sz_down[nex];
	}
}

void dfs1(int x, int pre, int &max_num, int &idx, int root) {
	int cnt = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == pre) continue;
		if (cut[nex]) continue;
		dfs1(nex, x, max_num, idx, root);
		cnt = max(cnt, sz_down[nex]);
	}
	cnt = max(cnt, sz_down[root] - sz_down[x]);
	if (cnt < max_num) {
		max_num = cnt;
		idx = x;
	}
}
int find_weight(int x) {
	memset(sz_down, 0, sizeof(sz_down));
	int max_num = 0x3f3f3f3f, idx;
	dfs(x, x);
	dfs1(x, x, max_num, idx, x);
	return idx;
}
/***********************************************************************/

int num[3], dep[MAXN];

void dfsdep(int x, int pre) {
	num[dep[x]]++;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre || cut[e.to]) continue;
		dep[e.to] = (dep[x] + e.v) % 3;
		dfsdep(e.to, x);
	}
}

int cal(int x, int pre) {
	num[0] = num[1] = num[2] = 0;
	dep[x] = pre;
	dfsdep(x, x);
	return num[0] * num[0] + num[1] * num[2] * 2;
}

int solve(int x) {
	int ans = cal(x, 0);
	cut[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (cut[e.to]) continue;
		ans -= cal(e.to, e.v);
		int root = find_weight(e.to);
		ans += solve(root);
	}
	return ans;
}

int main() {
	freopen("2152.in", "r", stdin);
	int a, b, c;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		c %= 3;
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	int root = find_weight(1);
	int ans = solve(root);
	int t = __gcd(ans, n * n);
	cout << ans / t << '/' << n * n / t << endl;


	return 0;
}
