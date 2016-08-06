#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;

const int MAXN = 20005;

int T, n, m;
vector<int> tr[MAXN];
int fa[MAXN];
int dep[MAXN], ans[MAXN];

void dfsdep(int x, int pre) {
	dep[x] = dep[pre] + 1;
	fa[x] = pre;
	ans[x] = 1;
	for (int i = 0; i < tr[x].size(); i++) {
		int nex = tr[x][i];
		if (nex == pre) continue;
		dfsdep(nex, x);
	}
}

void solve(int a, int b) {
	while (a != b) {
		if (dep[a] >= dep[b]) {
			ans[a]++;
			a = fa[a];
		} else {
			ans[b]++;
			b = fa[b];
		}
	}
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	int cas = 0;
	while (T--) {
		scanf("%d %d", &n, &m);
		int a, b;
		for (int i = 1; i <= n; i++)
			tr[i].clear();
		for (int i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b);
			tr[a].push_back(b);
			tr[b].push_back(a);
		}
		dfsdep(1, 0);
		for (int i = 0; i < m - n + 1; i++) {
			scanf("%d %d", &a, &b);
			solve(a, b);
		}
		int ret = 0x3f3f3f3f;
		for (int i = 2; i <= n; i++) {
			ret = min(ret, ans[i]);
		}
		printf("Case #%d: %d\n", ++cas, ret);
	}


	return 0;
}
