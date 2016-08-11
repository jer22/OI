#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n;
vector<int> edges[MAXN];
bool cut[MAXN];
/***************************树的重心************************************/
int sz_down[MAXN];
void dfs(int x, int pre) {
	sz_down[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		if (cut[nex]) continue;
		dfs(nex, x);
		sz_down[x] += sz_down[nex];
	}
}

void dfs1(int x, int pre, int &max_num, int &idx, int root) {
	// cout << x << ' ';
	int cnt = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		if (cut[nex]) continue;
		// cout << x << ' ' << nex << endl;
		dfs1(nex, x, max_num, idx, root);

		if (sz_down[nex] > cnt) cnt = sz_down[nex];
		// cout << cnt << endl;
	}
	if (sz_down[root] - sz_down[x] > cnt) cnt = sz_down[root] - sz_down[x];
	if (cnt < max_num) {
		max_num = cnt;
		idx = x;
	}
}
int find_weight(int x) {
	// memset(sz_down, 0, sizeof(sz_down));
	int max_num = 0x3f3f3f3f, idx;
	dfs(x, x);
	dfs1(x, x, max_num, idx, x);
	return idx;
}
/***********************************************************************/

int ans[MAXN];
void solve(int root, int dep) {
	cut[root] = 1;
	ans[root] = dep;
	for (int i = 0; i < edges[root].size(); i++) {
		int nex = edges[root][i];
		if (cut[nex]) continue;
		int r = find_weight(nex);
		solve(r, dep + 1);
	}

}

int main() {
	freopen("c.in", "r", stdin);
	// freopen("c.out", "w", stdout);
	int a, b;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	int root = find_weight(1);
	solve(root, 0);
	for (int i = 1; i <= n; i++) {
		if (i != 1) printf(" ");
		printf("%c", 'A' + ans[i]);
	}
	printf("\n");
	return 0;
}