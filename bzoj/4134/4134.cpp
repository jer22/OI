#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int MAXN = 100005;
const int MAXM = 4000005;

int n, m, tot = 0;
int hacked[MAXN], sg[MAXN], h[MAXN], fin[MAXN];
vector<int> edges[MAXN];
int root[MAXN], tr[MAXM][2], tag[MAXM], fulled[MAXM];

int newnode(int d, int num, int x = 0) {
	int rt = ++tot;
	if (d < 0) return fulled[rt] = 1, rt;
	tr[rt][(num >> d) & 1] = newnode(d - 1, num, x);
	return rt;
}

void rev(int d, int rt, int num) {
	if (!rt || d < 0) return;
	tag[rt] ^= num;
	swap(tr[rt][0], tr[rt][(num >> d) & 1]);
}

void pushdown(int d, int rt) {
	if (tag[rt]) {
		rev(d - 1, tr[rt][0], tag[rt]);
		rev(d - 1, tr[rt][1], tag[rt]);
		tag[rt] = 0;
	}
}

int merge(int d, int x, int y) {
	if (!x || !y) return x + y;
	int rt = ++tot;
	if (d < 0) return fulled[rt] = 1, rt;
	pushdown(d, x), pushdown(d, y);
	tr[rt][0] = merge(d - 1, tr[x][0], tr[y][0]);
	tr[rt][1] = merge(d - 1, tr[x][1], tr[y][1]);
	return fulled[rt] = fulled[tr[rt][0]] & fulled[tr[rt][1]], rt;
}
int mex(int x) {
	int t = 0;
	for (int i = m; ~i; i--){
		pushdown(i, x);
		if (!fulled[tr[x][0]]) x = tr[x][0];
		else x = tr[x][1], t |= 1 << i;
	}
	return t;
}

void dfs(int x, int pre) {
	for (int i = 0, nex; i < edges[x].size(); i++) if ((nex = edges[x][i]) != pre) {
		dfs(nex, x);
		h[x] ^= sg[nex];
	}
	if (!hacked[x]) root[x] = newnode(m, h[x], x);
	for (int i = 0, nex; i < edges[x].size(); i++) if ((nex = edges[x][i]) != pre) {
		rev(m, root[nex], h[x] ^ sg[nex]);
		root[x] = merge(m, root[x], root[nex]);
	}
	sg[x] = mex(root[x]);
}
void cal(int x,int pre,int z){
  z ^= sg[x] ^ h[x];
  if (!hacked[x] && !z) fin[x]=1;
  for (int i = 0, nex; i < edges[x].size(); i++) if ((nex = edges[x][i]) != pre) cal(nex, x, z);
}
int main() {
	freopen("4134.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &hacked[i]);
	while ((1 << m + 1) <= n) m++;
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 0);
	if (!sg[1]) printf("-1\n");
	else {
		cal(1, 0, sg[1]);
		for (int i = 1; i <= n; i++)
			if(fin[i]) printf("%d\n",i);
	}
	return 0;
}
