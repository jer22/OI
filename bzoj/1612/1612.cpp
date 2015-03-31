#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 105;

int n, m;
bool map[MAXN][MAXN];
int in[MAXN], out[MAXN];
int main() {
	freopen("1612.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		map[a][b] = 1;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				map[i][j] |= (map[i][k] & map[k][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (map[i][j]) in[i]++, out[j]++;
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (in[i] + out[i] == n - 1) ans++;
	cout << ans << endl;
	return 0;
}
