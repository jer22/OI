#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int ans = 0;
int parent[1010];

void init() {
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
}

int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

void un(int a, int b) {
	parent[find(a)] = find(b);
}

int main() {
	freopen("1536.in", "r", stdin);
	cin >> n;
	while (n) {
		init();
		ans = n - 1;
		cin >> m;
		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			if (find(a) != find(b)) {
				ans--;
				un(a, b);
			}
		}
		printf("%d\n", ans);
		cin >> n;
	}


	return 0;
}
