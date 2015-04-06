#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	int h, pos;
	bool operator < (const Node &n) const {
		return h < n.h;
	}
};

int n, q;
int height[50005];
int query[50005];
Node qq[50005];
int nex[50005], pre[50005];
int ans[50005];

int main() {
	freopen("1003.in", "r", stdin);
	while (~scanf("%d %d", &n, &q)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &height[i]);
		height[0] = height[n + 1] = -1;
		for (int i = 1; i <= q; i++) {
			scanf("%d", &query[i]);
			qq[i].h = query[i];
			qq[i].pos = i;
		}
		sort(qq + 1, qq + q + 1);
		for (int i = 1; i <= n; i++) {
			nex[i] = i + 1;
			pre[i] = i - 1;
		}
		nex[0] = 1;
		pre[n + 1] = n;
		memset(ans, 0, sizeof(ans));
		int cnt = 1;
		for (int i = 1; i <= q; i++) {
			for (int j = 0; j <= n; j = nex[j]) {
				// cout << j << endl;
				if (j && height[j] <= qq[i].h) {
					int x = nex[j], y = pre[j];
					pre[x] = y;
					nex[y] = x;
					if (height[j - 1] == -1 && height[j + 1] == -1) cnt--;
					else if (height[j - 1] != -1 && height[j + 1] != -1) cnt++;
					height[j] = -1;
				}
			}
			ans[qq[i].pos] = cnt;
		}
		for (int i = 1; i <= q; i++) {
			printf("%d\n", ans[i]);
		}
	}


	return 0;
}
