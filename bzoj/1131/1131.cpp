#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1000005;

int n;
vector<int> edges[MAXN];
long long siz[MAXN], tot[MAXN];

void dfs1(int x, int pre) {
	siz[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs1(nex, x);
		siz[x] += siz[nex];
		tot[x] += tot[nex] + siz[nex];
	}
}

void dfs2(int x, int pre) {
	if (x != 1) tot[x] = tot[pre] - siz[x] + n - siz[x];

	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs2(nex, x);
	}
}

int main() {
	freopen("1131.in", "r", stdin);
	scanf("%d", &n);
	int x, y;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &x, &y);
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	long long mx = 0, idx = 1;
	for (int i = 1; i <= n; i++) {
		if (tot[i] > mx) {
			idx = i;
			mx = tot[i];
		}
	}
	printf("%d\n", idx);
	return 0;
}
