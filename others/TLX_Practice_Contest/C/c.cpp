#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> edges[MAXN];
int siz[MAXN];

bool cmp(int a, int b) {
	return siz[a] > siz[b];
}

void dfs_solve(int x, int pre, int mid) {
	siz[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		dfs_solve(nex, x, mid);
	}
	sort(edges[x].begin(), edges[x].end(), cmp);
	for (int i = 0; i < edges[x].size(); i++) {
		if (i == mid) break;
		siz[x] += siz[edges[x][i]];
	}
}

bool solve(int x) {
	dfs_solve(1, 1, x);
	return siz[1] >= m;
}

int main() {
	// freopen("c.in", "r", stdin);
	int x;
	scanf("%d %d", &n, &m);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &x);
		edges[x].push_back(i);
	}
	int l = 0, r = MAXN;
	while (l < r) {
		int mid = l + r >> 1;
		if (solve(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
