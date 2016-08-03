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

int n, q;
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

bool stat[MAXN];
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 1);
	for (int i = 1; i <= n; i++) {
		insert(i, 1);
		stat[i] = 1;
	}
	// build(1, n, 1);
	scanf("%d", &q);
	char op[3];
	int x;
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		scanf("%d", &x);
		if (op[0] == 'Q') {
			// int ans = query(1, n, 1, fir[x], las[x]);
			int ans = get(las[x]) - get(fir[x] - 1);
			printf("%d\n", ans);
		} else {
			if (stat[x]) insert(fir[x], -1);
			else insert(fir[x], 1);
			stat[x] ^= 1;
			// update(1, n, 1, fir[x]);
			// update(1, n * 2, 1, las[x]);
		}
	}

	return 0;
}
