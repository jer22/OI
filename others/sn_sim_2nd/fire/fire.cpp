#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 50005;

int n;
vector<int> edges[MAXN];
long long w[MAXN], sum[MAXN], tot[MAXN];
int son1[MAXN], son2[MAXN], fa[MAXN];

void dfs_init(int x) {
	sum[x] = w[x];
	int fir = 0, sec = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == fa[x]) continue;
		fa[nex] = x;
		dfs_init(nex);

		sum[x] += sum[nex];
		tot[x] += tot[nex] + sum[nex];
		if (sum[nex] > fir) {
			sec = fir;
			fir = sum[nex];
			son2[x] = son1[x];
			son1[x] = nex;
		} else if (sum[nex] > sec) {
			sec = sum[nex];
			son2[x] = nex;
		}
	}

}

int rec[MAXN];
void update(int x, int y, long long dels, long long delt) {
	int h = 1;
	while (x) {

		sum[x] -= dels;
		tot[x] -= dels * h + delt;

		if (son1[x] == y) {
			if (son2[x] > sum[y]) {
				rec[x] = son1[x];
				son1[x] = son2[x];
			}
		}

		y = x;
		x = fa[x];
		h++;
	}
}

void recover(int x, int y, long long dels, long long delt) {
	long long h = 1;
	while (x) {

		sum[x] += dels;
		tot[x] += dels * h + delt;

		if (rec[x]) {
			son1[x] = rec[x];
			rec[x] = 0;
		}

		y = x;
		x = fa[x];
		h++;
	}
}

long long getans(int root) {
	long long ans = tot[root];
	int x = root;
	while (sum[root] - 2 * sum[son1[x]] < 0) {
		ans += sum[root] - 2 * sum[son1[x]];
		x = son1[x];
	}
	return ans;
}

long long solve(int x, int y) {
	long long t = sum[y];
	sum[y] = 0;
	update(x, y, t, tot[y]);
	sum[y] = t;

	long long ans = getans(1) + getans(y);
	// cout << tot[1] << endl;

	recover(x, y, sum[y], tot[y]);
	return ans;
}

int main() {
	freopen("fire.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &w[i]);
	}
	dfs_init(1);
	long long ans = 1000000000000000000LL;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			if (i == fa[edges[i][j]]) {
				// cout << i << ' ' << edges[i][j] << endl;
				// cout << solve(i, edges[i][j]) << endl;
				long long t = solve(i, edges[i][j]);
				if (t > 0)
					ans = min(ans, t);
			}
		}
	}
	// cout << solve(1, 3) << endl;
	cout << ans << endl;
	return 0;
}
