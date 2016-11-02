#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int n;
char s[MAXN];
long long ans[MAXN];
char op[3] = "DU";

void solve(bool flag) {
	int r = 1, num = 0;
	long long now = 0;
	for (int i = 1; i <= n; i++) {
		num++;
		now++;
		while (r <= n && num) {
			if (s[r] == op[(int)flag]) {
				now += (long long)r << 1ll;
				num--;
			}
			r++;
		}
		if (num) break;
		now -= (long long)(i << 1ll);
		if (!flag) ans[i] = now;
		else ans[n - i + 1] = now;
	}
}

int main() {
	// freopen("e.in", "r", stdin);
	cin >> n;
	cin >> s + 1;
	solve(0);
	for (int i = 1; i <= n >> 1; i++)
		swap(s[i], s[n - i + 1]);
	solve(1);
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];
	return 0;
}
