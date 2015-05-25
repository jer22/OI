#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 30005;

int n, q;
int value[MAXN];
vector<int> edges[MAXN];
int tot = 0;
int dfsver[MAXN << 1], first[MAXN];
int ST[MAXN << 1][20];
int siz[MAXN], deep[MAXN], max_son[MAXN];
int mark[MAXN], top[MAXN];
int fa[MAXN];

void dfs_size(int x, int pre, int dep) {
	dfsver[++tot] = x;
	first[x] = tot;

	deep[x] = dep;
	max_son[x] = 0;
	siz[x] = 1;

	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs_size(nex, x, dep + 1);
		dfsver[++tot] = x;
		fa[nex] = x;

		siz[x] += siz[nex];
		if (!max_son[x] || siz[nex] > siz[max_son[x]])
			max_son[x] = nex;
	}
}

int _num = 0;
void dfs_remark(int x, int pre, int topx) {
	top[x] = topx;
	mark[x] = ++_num;
	if (max_son[x]) dfs_remark(max_son[x], x, topx);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		if (max_son[x] != nex)
			dfs_remark(nex, x, nex);
	}

}

void RMQ() {
	for (int i = 1; i <= tot; i++)
		ST[i][0] = dfsver[i];
	for (int j = 1; (1 << j) <= tot; j++) {
		for (int i = 1; i + (1 << j) - 1 < tot; i++) {
			int a = ST[i][j - 1], b = ST[i + (1 << j - 1)][j - 1];
			ST[i][j] = deep[a] < deep[b] ? a : b;
		}
	}
}
int LCA(int a, int b) {
	int x = first[a], y = first[b];
	if (x > y) swap(x, y);
	int k = int(log(y - x + 1) / log(2));
	int l = ST[x][k], r = ST[y - (1 << k) + 1][k];
	int res = deep[l] < deep[r] ? l : r;
	return res;
}

int sum[MAXN << 2], mx[MAXN << 2];
void push_up(int rt) { sum[rt] = sum[lch] + sum[rch]; mx[rt] = max(mx[lch], mx[rch]); }
void build_tree(int l, int r, int rt) {
	int mid = l + r >> 1;
	sum[rt] = 0;
	mx[rt] = INT_MIN;
	if (l == r) return;
	build_tree(lson);
	build_tree(rson);
}
void insert(int l, int r, int rt, int id, int val) {
	if (l == r) {
		sum[rt] = mx[rt] = val;
		return;
	}
	int mid = l + r >> 1;
	if (id <= mid) insert(lson, id, val);
	else insert(rson, id, val);
	push_up(rt);
}

struct Node{
	int sum, mx;
	Node() {}
	Node(int a, int b) : sum(a), mx(b) {}
};
Node query(int l, int r, int rt, int L, int R) {
	if (L <= l && R >= r)
		return Node(sum[rt], mx[rt]);
	int mid = l + r >> 1;
	Node t;
	int sum = 0, mx = INT_MIN;
	if (L <= mid) {
		t = query(lson, L, R);
		sum += t.sum;
		mx = max(mx, t.mx);
	}
	if (mid < R) {
		t = query(rson, L, R);
		sum += t.sum;
		mx = max(mx, t.mx);
	};
	t = Node(sum, mx);
	return t;
}

int main() {
	freopen("1036.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &value[i]);
	scanf("%d", &q);
	dfs_size(1, 1, 1);
	RMQ();
	dfs_remark(1, 1, 1);
	build_tree(1, n, 1);
	for (int i = 1; i <= n; i++) insert(1, n, 1, mark[i], value[i]);
	char op[8];
	int x, y;
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		scanf("%d %d", &x, &y);
		if (op[0] == 'C') insert(1, n, 1, mark[x], y);
		else {
			int lca = LCA(x, y);
			int sum = 0;
			int mx = INT_MIN;
			while (x && deep[top[x]] >= deep[lca]) {
				Node t = query(1, n, 1, mark[top[x]], mark[x]);
				sum += t.sum;
				mx = max(mx, t.mx);
				x = fa[top[x]];
			}
			if (x && deep[x] >= deep[lca]) {
				Node t = query(1, n, 1, mark[lca], mark[x]);
				sum += t.sum;
				mx = max(mx, t.mx);
			}
			while (y && deep[top[y]] >= deep[lca]) {
				Node t = query(1, n, 1, mark[top[y]], mark[y]);
				sum += t.sum;
				mx = max(mx, t.mx);
				y = fa[top[y]];
			}
			if (y && deep[y] >= deep[lca]) {
				Node t = query(1, n, 1, mark[lca], mark[y]);
				sum += t.sum;
				mx = max(mx, t.mx);
			}
			sum -= query(1, n, 1, mark[lca], mark[lca]).sum;
			if (op[1] == 'M') printf("%d\n", mx);
			else printf("%d\n", sum);
		}
	}

	for (int i = 1; i <= tot; i++)
		cout << dfsver[i] << ' ';
	return 0;
}
