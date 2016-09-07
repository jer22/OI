#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400005;

int n;
int ans[MAXN];
vector<int> edges[MAXN];
int sz[MAXN], down[MAXN], up[MAXN];

void dfsdown(int x, int pre) {
	sz[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfsdown(nex, x);
		sz[x] += sz[nex];
		down[x] = max(down[x], down[nex]);

		if (sz[nex] - down[nex] > n / 2)
			ans[x] = 0;
	}
	if (sz[x] <= n >> 1) down[x] = sz[x];
}

void dfsup(int x, int pre) {
	if (n - sz[x] <= n / 2) up[x] = n - sz[x];
	int ma = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		
		up[nex] = max(up[nex], ma);
		up[nex] = max(up[nex], up[x]);
		ma = max(ma, down[nex]);
	}
	ma = 0;
	for (int i = edges[x].size() - 1; i >= 0; i--) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		up[nex] = max(up[nex], ma);
		ma = max(ma, down[nex]);
		if (n - sz[nex] - up[nex] > n / 2) {

			ans[nex] = 0;
		}
		dfsup(nex, x);
	}
	
}

int main() {
	freopen("e.in", "r", stdin);
	cin >> n;
	int a, b;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	memset(ans, -1, sizeof(ans));
	dfsdown(1, 1);
	
	dfsup(1, 1);
	for (int i = 1; i <= n; i++) {
		// cout << up[i] << endl;
		if (i > 1) cout << ' ';
		if (!ans[i]) cout << 0;
		else cout << 1;
	}
	cout << endl;


	return 0;
}
