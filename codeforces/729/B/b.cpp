#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int n, m;
int arr[MAXN][MAXN];
int l[MAXN], r[MAXN], u[MAXN], d[MAXN];
int main() {
	cin >> n >> m;
	memset(l, 0x3f, sizeof(l));
	memset(r, -1, sizeof(r));
	memset(u, 0x3f, sizeof(u));
	memset(d, -1, sizeof(d));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
			if (!arr[i][j]) continue;
			l[i] = min(j, l[i]);
			r[i] = max(j, r[i]);
			u[j] = min(i, u[j]);
			d[j] = max(i, d[j]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j]) continue;
			ans += (j > l[i]) + (j < r[i]) + (i > u[j]) + (i < d[j]);
		}
	}
	cout << ans << endl;
	return 0;
}
