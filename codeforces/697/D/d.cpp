#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
vector<int> edges[MAXN];

double ans[MAXN];
int siz[MAXN], fa[MAXN];

void dfs(int x) {
	siz[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		dfs(edges[x][i]);
		siz[x] += siz[edges[x][i]];
	}
}

void hh(int x) {
	if (x != 1) {
		ans[x] = ans[fa[x]] + double(siz[fa[x]] - siz[x] - 1) / 2 + 1;
	}
	for (int i = 0; i < edges[x].size(); i++)
		hh(edges[x][i]);
}

int main() {
	freopen("d.in", "r", stdin);
	cin >> n;
	for (int i = 2; i <= n; i++) {
		cin >> fa[i];
		edges[fa[i]].push_back(i);
	}
	ans[1] = 1.0;
	dfs(1);
	hh(1);
	for (int i = 1; i <= n; i++) {
		if (i != 1) printf(" ");
		printf("%.10lf", ans[i]);
	}
	printf("\n");

	return 0;
}
