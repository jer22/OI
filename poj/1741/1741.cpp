#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

const int MAXN = 10005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, k;
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

int dist[MAXN];
int dist2[MAXN];
int tot = 0;
void getdist(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge nex = edges[x][i];
		if (cut[nex.to]) continue;
		if (nex.to == pre) continue;
		dist[nex.to] = dist[x] + nex.v;
		dist2[tot++] = dist[nex.to];
		getdist(nex.to, x);
	}
}
int getB(int root, int k) {
	dist[root] = 0;
	tot = 0;
	dist[tot++] = 0;
	getdist(root, root);
	sort(dist2, dist2 + tot);
	int l = 0, r = tot - 1;
	int ans = 0;
	while (l < tot && r >= 0) {
		if (dist2[l] + dist2[r] > k) {
			r--;
		} else {
			ans += r + 1;
			l++;
		}
	}
	return ans;
}
int solve(int root) {
	int B = getB(root, k);
	int C = 0;
	cut[root] = 1;
	int ans = 0;
	for (int i = 0; i < edges[root].size(); i++) {
		Edge nex = edges[root][i];
		if (cut[nex.to]) continue;
		C += getB(nex.to, k - nex.v * 2);
	}
	B--;
	// cout << root << ' ' << C << endl;
	ans = B - C;
	for (int i = 0; i < edges[root].size(); i++) {
		Edge nex = edges[root][i];
		if (cut[nex.to]) continue;
		int r = find_weight(nex.to);
		ans += solve(r);
	}
	return ans;
}

int main() {
	freopen("1741.in", "r", stdin);
	while (~scanf("%d %d", &n, &k) && n && k) {
		int a, b, c;
		memset(cut, 0, sizeof(cut));
		for (int i = 0; i <= n; i++) edges[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		int root = find_weight(1);
		cout << solve(root) / 2 << endl;

	}


	return 0;
}
