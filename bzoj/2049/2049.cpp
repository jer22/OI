#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

const int MAXN = 10005;

int n, m;
bool rev[MAXN];
int fa[MAXN], tr[MAXN][2];
int stack[MAXN], top = 0;
void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (rev[x]) {
		rev[x] ^= 1; rev[l] ^= 1; rev[r] ^= 1;
		swap(tr[x][0], tr[x][1]);
	}
}
inline bool isroot(int x) {
	return tr[fa[x]][0] != x && tr[fa[x]][1] != x;
}
void rotate(int x) {
	int y = fa[x], z = fa[y];
	int l, r;
	if (tr[y][0] == x) l = 0;
	else l = 1;
	r = l ^ 1;
	if (!isroot(y)) {
		if (tr[z][0] == y) tr[z][0] = x;
		else tr[z][1] = x;
	}
	fa[x] = z;
	fa[y] = x;
	fa[tr[x][r]] = y;
	tr[y][l] = tr[x][r];
	tr[x][r] = y;
}
void splay(int x) {
	top = 0;
	stack[++top] = x;
	for (int i = x; !isroot(i); i = fa[i])
		stack[++top] = fa[i];
	while (top) pushdown(stack[top--]);
	while (!isroot(x)) {
		int y = fa[x], z = fa[y];
		if (!isroot(y)) {
			if (tr[y][0] == x ^ tr[z][0] == y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x) {
	for (int t = 0; x; t = x, x = fa[x])
		splay(x), tr[x][1] = t;
}
void makeroot(int x) {
	access(x);
	splay(x);
	rev[x] ^= 1;
}
void link(int x, int y) {
	makeroot(x);
	fa[x] = y;
	splay(x);
}
void cut(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	tr[y][0] = fa[tr[y][0]] = 0;
}
int find(int x) {
	access(x);
	splay(x);
	while (tr[x][0]) x = tr[x][0];
	return x;
}

void query(int x, int y) {
	if (find(x) == find(y)) printf("Yes\n");
	else printf("No\n");
}

int main() {
	freopen("2049.in", "r", stdin);
	scanf("%d %d", &n, &m);
	char op[10];
	int x, y;
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		scanf("%d %d", &x, &y);
		if (op[0] == 'Q') query(x, y);
		else if (op[0] == 'C') link(x, y);
		else cut(x, y);
	}

	return 0;
}
