#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int n = 30005;

int m;
int fa[n], cnt[n], siz[n];

int find(int p) {
	if (p == fa[p]) return p;
	int t = find(fa[p]);
	cnt[p] += cnt[fa[p]];
	fa[p] = t;
	return t;
}

void un(int x, int y) {
	int a = find(x);
	int b = find(y);
	fa[a] = b;
	cnt[a] += siz[b];
	siz[b] += siz[a];
}

int main() {
	freopen("1540.in", "r", stdin);
	scanf("%d", &m);
	for (int i = 0; i < n; i++) {
		fa[i] = i;
		siz[i] = 1;
		cnt[i] = 0;
	}

	int x, y;
	char op[5];
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		scanf("%d %d", &x, &y);
		if (op[0] == 'M') un(x, y);
		else {
			if (find(x) != find(y)) cout << -1 << endl;
			else cout << abs(cnt[x] - cnt[y]) - 1 << endl;
		}
	}
	return 0;
}
