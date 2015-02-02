#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 5005

using namespace std;

long long x0, a, b, c, d;
int n, m, q;
int t[MAXN * MAXN];
int pos[MAXN * MAXN];
int l[MAXN], r[MAXN];
int u, v;
int tot = 0;
int main() {
	freopen("3671.in", "r", stdin);
	cin >> x0 >> a >> b >> c >> d;
	cin >> n >> m >> q;
	for (int i = 1; i <= n * m; i++) t[i] = i;
	for (int i = 1; i <= n * m; i++) {
		x0 = (a * x0 * x0 + b * x0 + c) % d;
		swap(t[i], t[x0 % i + 1]);
	}
	for (int i = 0; i < q; i++) {
		cin >> u >> v;
		swap(t[u], t[v]);
	}
	for (int i = 1; i <= n * m; i++) pos[t[i]] = i;
	for (int i = 1; i <= n; i++)
		l[i] = 1, r[i] = m;
	for (int i = 1; i <= n * m; i++) {
		int position = pos[i];
		int x = position / m + 1;
		int y = position % m;
		if (!y) y = m, x--;
		if (y < l[x] || y > r[x]) continue;
		for (int j = x + 1; j <= n; j++)
			l[j] = max(l[j], y);
		for (int j = 0; j <= x - 1; j++)
			r[j] = min(r[j], y);
		if (i > 1) cout << " ";
		cout << i;
	}
	cout << endl;
	return 0;
}
