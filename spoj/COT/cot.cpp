#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n, q, tot, cnt = 0;
int arr[MAXN], t[MAXN];
int root[MAXN], ls[MAXN * 80], rs[MAXN * 80], siz[MAXN * 80];
vector<int> edges[MAXN];

inline int readint()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

void inithash() {
	for (int i = 1; i <= n; i++)
		t[i] = arr[i];
	sort(t + 1, t + n + 1);
	tot = unique(t + 1, t + n + 1) - t - 1;
}

int get(int x) {
	return lower_bound(t + 1, t + tot + 1, x) - t;
}

void insert(int l, int r, int x, int &y, int v) {
	y = ++cnt;
	siz[y] = siz[x] + 1;
	if (l == r) return;
	ls[y] = ls[x], rs[y] = rs[x];
	int m = l + r >> 1;
	if (v <= m) insert(l, m, ls[x], ls[y], v);
	else insert(m + 1, r, rs[x], rs[y], v);
}

int id = 0, fa[MAXN][21], deep[MAXN], pos[MAXN];
void dfs(int x) {
	pos[x] = ++id;
	deep[x] = deep[fa[x][0]] + 1;
	insert(1, tot, root[pos[fa[x][0]]], root[id], get(arr[x]));
	for (int i = 1; i <= 16; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == fa[x][0]) continue;
		fa[nex][0] = x;
		dfs(nex);
	}
}

int LCA(int x, int y) {
	if (deep[x] < deep[y]) swap(x, y);
	int tmp = deep[x] - deep[y];
	for (int i = 0; i <= 16; i++)
		if ((1 << i) & tmp) x = fa[x][i];
	for (int i = 16; i >= 0; i--)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

int query(int x, int y, int k) {
	int l = 1, r = tot;
	int lca = LCA(x, y);
	int a = root[pos[x]], b = root[pos[y]], c = root[pos[lca]], d = root[pos[fa[lca][0]]];
	while (l < r) {
		int m = l + r >> 1;
		int tmp = siz[ls[a]] + siz[ls[b]] - siz[ls[c]] - siz[ls[d]];
		if (tmp >= k) {
			r = m;
			a = ls[a], b = ls[b], c = ls[c], d = ls[d];
		}
		else {
			l = m + 1;
			k -= tmp;
			a = rs[a], b = rs[b], c = rs[c], d = rs[d];
		}
	}
	return t[l];
}

int main() {
	freopen("cot.in", "r", stdin);
	n = readint();
	q = readint();
	for (int i = 1; i <= n; i++) {
		arr[i] = readint();
	}
	int a, b, c;
	for (int i = 1; i < n; i++) {
		a = readint(), b = readint();
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	inithash();
	dfs(1);
	while (q--) {
		a = readint(), b = readint(), c = readint();
		printf("%d\n", query(a, b, c));
	}
	return 0;
}
