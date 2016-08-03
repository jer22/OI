#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 100005;

int n, q, root;
vector<vector<int> > edges(MAXN);

int tot = 0;
int fir[MAXN], las[MAXN];
void dfs(int pre, int x) {
	tot++;
	fir[x] = tot;
	int s = edges[x].size();
	for (int i = 0; i < s; i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(x, nex);
	}
	las[x] = tot;
	// ver[tot] = x;
}

int c[MAXN];
int lowbit(int x) {
	return x & (-x);
}

void insert(int x, int p) {
	while (x <= n) {
		c[x] += p;
		x += lowbit(x);
	}
}
int get(int x) {
	int ans = 0;
	while (x >= 1) {
		ans += c[x];
		x -= lowbit(x);
	}
	return ans;
}

int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%d %d", &n, &root)) {
		if (!n && !root) break;
		int a, b;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		memset(c, 0, sizeof(c));
		tot = 0;
		dfs(root, root);
		// build(1, n, 1);
		for (int i = 1; i <= n; i++) {
			int ans = get(las[i]) - get(fir[i] - 1);
			if (i > 1) printf(" ");
			printf("%d", ans);
			insert(fir[i], 1);
		}
		printf("\n");
	}

	return 0;
}
