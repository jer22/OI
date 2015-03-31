#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch
#define root 1, n, 1

using namespace std;

const int MAXN= 100005;
const int INF = 0x3f3f3f3f;

int n, m, k;
vector<int> edges[MAXN];
int in[MAXN];
int mi[MAXN << 2];

void build(int l, int r, int rt) {
	if (l == r) {
		mi[rt] = in[l];
		return;
	}
	int mid = l + r >> 1;
	build(lson);
	build(rson);
	mi[rt] = min(mi[lch], mi[rch]);
}

int query(int l, int r, int rt, int c) {
	if (l == r) return l;
	int mid = l + r >> 1;
	if (mi[rch] <= c) return query(rson, c);
	else return query(lson, c);
}

void insert(int l, int r, int rt, int p, int v) {
	if (l == r) {
		mi[rt] += v;
		return;
	}
	int mid = l + r >> 1;
	if (p <= mid) insert(lson, p, v);
	else insert(rson, p, v);
	mi[rt] = min(mi[lch], mi[rch]);
}

int main() {
	freopen("5195.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &m, &k)) {
		memset(in, 0, sizeof(in));
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			in[b]++;
		}
		build(root);
		int num = n;
		while (num--) {
			int t = query(root, k);
			cout << t << " \n"[num == 0];
			k -= in[t];
			insert(root, t, INF);
			for (int i = 0; i < edges[t].size(); i++) {
				int j = edges[t][i];
				insert(root, j, -1);
				in[j]--;
			}
		}
	}
	return 0;
}
