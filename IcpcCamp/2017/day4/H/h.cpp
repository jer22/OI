#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;

int n, s, m, mxdeep;


int T;
vector<int> edges[MAXN];
int deep[MAXN], siz[MAXN], fa[MAXN][22];
bool vis[MAXN];


int getlca(int x, int y) {
	if (deep[x] > deep[y]) swap(x, y);
	int a = x, b = y;
	int t = deep[b] - deep[a];
	 for (int i = 0; i <= 18; i++)
	 	if ((1 << i) & t) b = fa[b][i];
	for (int i = 18; i >= 0; i--)
		if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
	if (a != b) a = fa[a][0];
	return a;
}

void dfs(int x, int pre) {
	deep[x] = deep[pre] + 1;
	siz[x] = 1;
	mxdeep = max(mxdeep, deep[x]);
	fa[x][0] = pre;
	for (int i = 1; i <= 18; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (auto nex : edges[x]) if (nex != pre) {
		dfs(nex, x);
		siz[x] += siz[nex];
	}
}

struct Node{
	int dep, id;
	Node() {}
	Node(int a, int b) : dep(a), id(b) {}
	bool operator < (const Node &n) const {
		return dep > n.dep;
	}
};
vector<Node> ps;
int main() {
	freopen("h.in", "r", stdin);
	// freopen("h.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &s, &m);
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			vis[i] = 0;
		}
		for (int i = 1, a, b; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		mxdeep = 0;
		dfs(m, 0);
		ps.clear();
		for (int i = 1; i <= n; i++) {
			if (siz[i] == 1 && i != s) ps.push_back(Node(deep[i], i));
		}
		sort(ps.begin(), ps.end());
		if (ps.size() == 0) {
			printf("%d\n", n - 1);
			continue;
		}

		int ans = deep[s] - deep[m] + ps[0].dep - 1;
		// cout << ans << endl;
		int now = s;
		vis[s] = 1;
		int tmp = deep[s] - deep[m];
		// for (int i = 0; i < ps.size(); i++)
		for (int i = 0; i < ps.size(); ) {
			bool flag = false;
			do {

				int x = ps[i].id;
				int t = 0;
				int lca = getlca(now, x);
				while (x != m) {
					if (vis[x]) break;
					vis[x] = 1;
					if (x == lca) {
						break;
					}
					x = fa[x][0];
					t++;
				}
				while (now != lca) {
					now = fa[now][0];
					vis[now] = 1;
				}

				tmp += t * 2;
				if (now == m) {
					flag = true;
					break;
				}
				i++;
			} while (i < ps.size() && ps[i].dep == ps[i - 1].dep);
			if (flag) break;
			if (i < ps.size()) {
				ans = min(ans, tmp + ps[i].dep - 1);
			} else if (i == ps.size()) ans = min(ans, tmp);
		}
		cout << ans << endl;
	}


	return 0;
}
