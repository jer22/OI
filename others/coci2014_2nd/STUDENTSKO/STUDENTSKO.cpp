#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 5005;

struct Node{
	int pos, val;
	Node() {}
	Node(int a, int b) : pos(a), val(b) {}
	bool operator < (const Node &n) const {
		if (val != n.val) return val < n.val;
		return pos < n.pos;
	}
};

int n, k;
Node arr[MAXN];
int dp[MAXN];
int refl[MAXN];

int solve() {
	int mx = 0;
	for (int i = 1; i <= n; i++) {
		// cout << refl[i] << endl;
		dp[i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			if (refl[j] <= refl[i]) dp[i] = max(dp[i], dp[j] + 1);
		}
		mx = max(mx, dp[i]);
	}
	return mx;
}

int main() {
	freopen("STUDENTSKO.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].val);
		arr[i].pos = i;
	}
	sort(arr + 1, arr + n + 1);
	int tot = 0;
	for (int i = 1; i <= n; i += k) {
		tot++;
		for (int j = 1; j <= k; j++)
			refl[arr[i + j - 1].pos] = tot;
	}
	int ans = n - solve();
	cout << ans << endl;
	return 0;
}
