/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#pragma comment(linker, "/STACK:10240000,10240000")
#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 300005;

int n, q;
vector<int> edges[MAXN];
int id[MAXN], vis[MAXN << 1];
int depth[MAXN];
int tot;

void dfs(int x, int pre, int dep) {
	tot++;
	id[x] = tot;
	vis[tot] = x;
	depth[x] = dep;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x, dep + 1);
		vis[++tot] = x;
	}
}

int early[MAXN][21];
int later[MAXN][21];

int st[MAXN << 1][21];

int queryl(int a, int b) {
	int k = log(b - a + 1) / log(2);
	return min(early[a][k], early[b - (1 << k) + 1][k]);
}

int queryr(int a, int b) {
	int k = log(b - a + 1) / log(2);
	return max(later[a][k], later[b - (1 << k) + 1][k]);
}

int query(int l, int r) {
	int k = log(r - l + 1) / log(2);
	int a = st[l][k];
	int b = st[r - (1 << k) + 1][k];
	if (depth[a] < depth[b]) return a;
	return b;
}

int main() {
	freopen("c.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int a, b;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		tot = 0;
		dfs(1, 1, 1);

		for (int i = 1; i <= n; i++) {
			early[i][0] = id[i];
			later[i][0] = id[i];
		}
		for (int j = 1; j <= 20; j++) {
			for (int i = 1; i <= n; i++) {
				if (i + (1 << j) - 1 <= n) {
					early[i][j] = min(early[i][j - 1], early[i + (1 << j - 1)][j - 1]);
					later[i][j] = max(later[i][j - 1], later[i + (1 << j - 1)][j - 1]);
				}
			}
		}
		for (int i = 1; i <= tot; i++)
			st[i][0] = vis[i];
		for (int j = 1; j <= 20; j++) {
			for (int i = 1; i <= tot; i++) {
				if (i + (1 << j) - 1 <= tot) {
					int a = st[i][j - 1];
					int b = st[i + (1 << j - 1)][j - 1];
					if (depth[a] < depth[b]) st[i][j] = a;
					else st[i][j] = b;
				}
			}
		}
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &a, &b);
			int l = queryl(a, b);
			int r = queryr(a, b);
			int ans = query(l, r);
			cout << ans << endl;
		}
	}


	return 0;
}
	