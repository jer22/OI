#include <bits/stdc++.h>

using namespace std;

int n;
int a[100005], b[100005];

int solve(int *s, int *e) {
	int ans = 0;
	int la = 0, lb = 0;
	int ra = n - 1, rb = n - 1;
	while (la <= ra && lb <= rb) {
		if (s[la] > e[lb]) ans += 2, la++, lb++;
		else if (s[ra] > e[rb]) ans += 2, ra--, rb--;
		else ans += (s[la] == e[rb]), la++, rb--;
	}
	return ans;
}

int main() {
	freopen("1034.in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	sort(a, a + n);
	sort(b, b + n);
	cout << solve(a, b) << ' ' << n * 2 - solve(b, a);
	return 0;
}
