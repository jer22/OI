#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m;

int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> m;
	int a, b;
	int ans = 0x3f3f3f3f;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		ans = min(ans, b - a + 1);
	}
	cout << ans << endl;
	for (int i = 0; i < n; i++)
		cout << i % ans << " \n"[i == n - 1];
	

	return 0;
}
