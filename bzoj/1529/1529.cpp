#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 1000005;

int n;
int fa[MAXN];

int find(int p) {
	if (p == fa[p]) return p;
	return fa[p] = find(fa[p]);
}

void un(int a, int b) {
	fa[find(a)] = find(b);
}

int main() {
	freopen("1529.in", "r", stdin);
	scanf("%d", &n);
	int a;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		if (find(a) != find(i)) un(i, a);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (i == fa[i]) ans++;
	printf("%d\n", ans);
	return 0;
}
