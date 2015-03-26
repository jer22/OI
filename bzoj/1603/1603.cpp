#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n;
Edge fa[1005];
int main() {
	freopen("1603.in", "r", stdin);
	scanf("%d", &n);
	int a, b, c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		fa[b] = Edge(a, c);
	}
	int ans = 0;
	int x = n;
	while (x != 1) {
		ans ^= fa[x].v;
		x = fa[x].to;
	}
	cout << ans << endl;
	return 0;
}
