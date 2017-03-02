#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int n;
int arr[MAXN];
map<long long, int> dp[65];
int sg[62] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10};

int cal(int x, long long ban) {
	if (dp[x].count(ban)) return dp[x][ban];
	long long fuck = 0;
	for (int i = 1; i <= x; i++) {
		if ((ban >> i) & 1) continue;
		fuck |= 1ll << cal(x - i, ban | (1ll << i));
	}
	for (int i = 0; i <= 61; i++)
		if (fuck >> i & 1 ^ 1) return dp[x][ban] = i;
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	int ans = 0;
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		ans ^= sg[x];
	}
	if (ans) cout << "NO\n";
	else cout << "YES\n";
	


	return 0;
}
