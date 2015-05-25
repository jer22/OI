#include <bits/stdc++.h>

using namespace std;

const int MOD = 10000;

struct Node{
	int p, a;
	friend istream& operator >> (istream &_, Node &x) {
		scanf("%d %d", &x.p, &x.a);
		return _;
	}
}p[1005];

int power(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = a * a % MOD)
		if (b & 1) ans = ans * a % MOD;
	return ans;
}

int n;
int main() {
	// freopen("1408.in", "r", stdin);
	scanf("%d", &n);
	int ans1 = 0, ans2 = 0;
	int re = 1;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		re = re * power(p[i].p, p[i].a) % MOD;
		if (p[i].p == 2) continue;
		int t1 = (ans1 + ans2 * (p[i].p - 1)) % MOD;
		int t2 = (ans2 + (ans1 + 1) * (p[i].p - 1)) % MOD;
		ans1 = t1;
		ans2 = t2;
	}
	int ans3 = (re - 1 - ans1 - ans2 + MOD * 3) % MOD;
	printf("%d\n%d\n%d\n", ans1, ans2, ans3);
	return 0;
}
