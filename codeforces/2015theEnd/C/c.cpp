#include <bits/stdc++.h>

using namespace std;

int n, m, q;
char arr[505][505];
long long dph[505][505];
long long dpv[505][505];
int a, b, c, d;
int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		scanf("%s", arr[i] + 1);
	cin >> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dph[i][j] = dph[i][j - 1];
			dpv[i][j] = dpv[i - 1][j];
			if (arr[i][j] == arr[i][j - 1] && arr[i][j] == '.') dph[i][j]++;
			if (arr[i][j] == arr[i - 1][j] && arr[i][j] == '.') dpv[i][j]++;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dph[i][j] += dph[i - 1][j];
			dpv[i][j] += dpv[i][j - 1];
		}
	}
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		long long ans = dpv[c][d] + dph[c][d];
		ans -= dpv[c][b - 1];
		ans -= dph[c][b];
		ans -= dpv[a][d];
		ans -= dph[a - 1][d];
		ans += dpv[a][b - 1];
		ans += dph[a - 1][b];
		cout << ans << endl;
	}

	return 0;
}
