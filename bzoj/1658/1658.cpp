#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n, m;
int dist[10005];
int deg[10005];
int s[10005], t[10005];
int ns, nt;
int main() {
	freopen("1658.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &dist[i]);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		deg[a]++, deg[b]--;
	}
	for (int i = 1; i <= n; i++) {
		if (deg[i] > 0) while (deg[i]--) s[ns++] = dist[i];
		else if (deg[i] < 0) while (deg[i]++) t[nt++] = dist[i];
	}
	sort(s, s + ns);
	sort(t, t + nt);
	int ans = 0;
	for (int i = 0; i < ns; i++) {
		// cout << t[i] << endl;
		ans += abs(s[i] - t[i]);
	}
	cout << ans << endl;
	return 0;
}
