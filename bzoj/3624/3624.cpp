#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, k;
int top;
int u[100005], v[100005], c[100005], ans[100005];
int fa[20005];
bool vis[100005];
int num[2];
inline int find(int p) {
	if (p == fa[p]) return p;
	return fa[p] = find(fa[p]);
}

void solve(int x, int lim) {
	for (int i = 0; i < m; i++) {
		if (c[i] == x && num[x] < lim) {
			int p = find(u[i]);
			int q = find(v[i]);
			if (p != q) {
				fa[p] = q;
				ans[++top] = i;
				vis[i] = 1;
				num[x]++;
			}
		}
	}
}

int main() {
	freopen("3624.in", "r", stdin);
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		cin >> u[i] >> v[i] >> c[i];
	}
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	solve(1, INF);
	solve(0, INF);
	if (num[0] + num[1] != n - 1 || num[0] > k) {
		cout << "no solution" << endl;
		return 0;
	}
	top = num[0] = num[1] = 0;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 0; i < m; i++) {
		if (!c[i] && vis[i]) {
			int p = find(u[i]);
			int q = find(v[i]);
			if (p != q) {
				num[0]++;
				fa[p] = q;
				ans[++top] = i;
			}
		}
	}
	solve(0, k);
	solve(1, INF);
	if (num[0] < k) {
		printf("no solution\n");
		return 0;
	}
	for (int i = 1; i <= top; i++) {
		printf("%d %d %d\n", u[ans[i]], v[ans[i]], c[ans[i]]);
	}

	return 0;
}
