#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int T;
int n, hash_siz;
long long k;
long long val[MAXN];
long long qval[MAXN];
long long t[MAXN << 2];
vector<int> edges[MAXN];

void inithash() {
	for (int i = 1; i <= n; i++)
		t[i] = val[i], t[i + n] = qval[i];
	sort(t + 1, t + n + n + 1);
	hash_siz = unique(t + 1, t + n + n + 1) - t - 1;
}

int get(long long x) {
	return lower_bound(t + 1, t + 1 + hash_siz, x) - t;
}

bool vis[MAXN];

int tot = 0;
int ver[MAXN], ed[MAXN], sta[MAXN];
long long ans[MAXN][2];

void dfs(int x) {
	ver[++tot] = x;
	sta[x] = tot;
	for (int i = 0; i < edges[x].size(); i++)
		dfs(edges[x][i]);
	ed[x] = tot;
}

int c[MAXN << 1];
int lowbit(int x) {
	return x & (-x);
}

void add(int x, int p) {
	for (int i = x; i <= n + n; i += lowbit(i)) {
		c[i] += p;
	}
}

int getsum(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		ans += c[i];
	}
	return ans;
}

struct Node{
	int val, pos, sty, idx;
	Node() {}
	Node(int d, int a, int b, int c) : idx(d), val(a), pos(b), sty(c) {}
	bool operator < (const Node &n) const {
		return pos < n.pos;
	}
};

vector<Node> nodes;
int main() {
	freopen("1010.in", "r", stdin);
	while (~scanf("%d", &T)) {
		while (T--) {
			scanf("%d %lld", &n, &k);
			for (int i = 1; i <= n; i++) {
				edges[i].clear();
				scanf("%lld", &val[i]);
				if (val[i]) qval[i] = k / val[i];
				else qval[i] = 1000000000000000000;
			}
			inithash();
			int a, b;
			int root;
			memset(vis, 0, sizeof(vis));
			for (int i = 1; i < n; i++) {
				scanf("%d %d", &a, &b);
				edges[a].push_back(b);
				vis[b] = 1;
			}
			for (int i = 1; i <= n; i++) {
				if (!vis[i]) {
					root = i;
					break;
				}
			}
			tot = 0;
			dfs(root);
			memset(c, 0, sizeof(c));
			nodes.clear();
			for (int i = 1; i <= n; i++) {
				if (!val[i]) ans[i][0] = ed[i], ans[i][1] = sta[i];
				else {
					nodes.push_back(Node(i, get(qval[i]), ed[i], 0));
					nodes.push_back(Node(i, get(qval[i]), sta[i], 1));
					// cout << sta[i] << ' ' << ed[i] << endl;
				}
			}
			sort(nodes.begin(), nodes.end());
			int idx = 0;
			for (int i = 1; i <= n; i++) {
				int x = ver[i];
				add(get(val[x]), 1);
				while (idx < nodes.size() && nodes[idx].pos == i) {
					// cout << i << ' ' << nodes[idx].idx << ' ' << nodes[idx].sty << ' ' << nodes[idx].val << endl;
					// cout << getsum(nodes[idx].val) << endl;
					ans[nodes[idx].idx][nodes[idx].sty] = getsum(nodes[idx].val);
					idx++;
				}
			}
			long long ret = 0;
			for (int i = 1; i <= n; i++) {

				ret += ans[i][0] - ans[i][1];
			}
			printf("%lld\n", ret);
		}

	}
	

	return 0;
}
