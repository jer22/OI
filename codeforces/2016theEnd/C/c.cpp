#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 200005;
const int INF = 0x3f3f3f3f;

int n;
int main() {
	// freopen("c.in", "r", stdin);
	scanf("%d", &n);
	int change, div;
	bool flag = true;
	int l = -INF, r = INF;
	scanf("%d %d", &change, &div);
	if (div == 1) l = 1900;
	else r = 1899;
	int nc, nd;
	for (int i = 2; i <= n; i++) {
		scanf("%d %d", &nc, &nd);
		if (!flag) continue;
		if (l != -INF) l += change;
		if (r != INF) r += change;
		if (nd == 1) {
			if (r < 1900) {
				flag = false;
				continue;
			}
			l = max(l, 1900);
		} else {
			if (l > 1899) {
				flag = false;
				continue;
			}
			r = min(r, 1899);
		}
		change = nc;
	}
	if (!flag) printf("Impossible\n");
	else if (r == INF) printf("Infinity\n");
	else printf("%d\n", r + change);
	return 0;
}
