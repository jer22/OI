#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000005;

int n;
int vis[MAXN], pre[MAXN];
int main() {
	// freopen("b.in", "r", stdin);
	int x;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		vis[x] = 1;

	}
	for (int i = 2; i < MAXN; i++)
		pre[i] = vis[i - 1] ? i - 1 : pre[i - 1];
	int ans = 0;
	for (int i = 1; i < MAXN; i++) {
		if (!vis[i]) continue;
		for (int j = i + i; j < MAXN; j += i) {
			ans = max(ans, pre[j] % i);
		}
	}
	cout << ans << endl;
	return 0;
}
