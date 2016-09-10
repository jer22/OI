#include <bits/stdc++.h>

#define p(i, j) ((i) * (m + 2) + (j))

using namespace std;

int n, m, q;
int arr[1005][1005];
int rig[1100005], down[1100005];

int find(int x, int y) {
	int pos = 0;
	while (x--) pos = down[pos];
	while (y--) pos = rig[pos];
	return pos;
}

int main() {
	freopen("e.in", "r", stdin);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= m + 1; j++) {
			rig[p(i, j)] = p(i, j + 1);
			down[p(i, j)] = p(i + 1, j);
		}
	}

	int x1, y1, x2, y2, h, w;
	while (q--) {
		scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &h, &w);
		int a = find(x1 - 1, y1), b = find(x2 - 1, y2);
		int c = a, d = b;
		for (int i = 0; i < h; i++)
			c = down[c], d = down[d];
		for (int i = 0; i < w; i++) {
			swap(down[a], down[b]);
			swap(down[c], down[d]);
			a = rig[a], b = rig[b];
			c = rig[c], d = rig[d];
		}
		a = find(x1, y1 - 1), b = find(x2, y2 - 1);
		c = a, d = b;
		for (int i = 0; i < w; i++)
			c = rig[c], d = rig[d];
		for (int i = 0; i < h; i++) {
			swap(rig[a], rig[b]);
			swap(rig[c], rig[d]);
			a = down[a], b = down[b];
			c = down[c], d = down[d];
		}
	}
	int s = 0;
	for (int i = 1; i <= n; i++) {
		s = down[s];
		int t = s;
		for (int j = 1; j <= m; j++) {
			t = rig[t];
			if (j != 1) printf(" ");
			printf("%d", arr[t / (m + 2)][t % (m + 2)]);
		}
		printf("\n");
	}

	return 0;
}
