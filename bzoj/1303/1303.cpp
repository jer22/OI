#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, pos;
int sum[MAXN], l[MAXN << 1], r[MAXN << 1];
int main() {
	freopen("1303.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int x;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		if (x > m) sum[i] = 1;
		else if (x == m) pos = i;
		else sum[i] = -1;
	}
	l[n] = r[n] = 1;
	for (int i = pos - 1; i >= 1; i--) {
		sum[i] += sum[i + 1];
		l[sum[i] + n]++;
	}
	for (int i = pos + 1; i <= n; i++) {
		sum[i] += sum[i - 1];
		r[sum[i] + n]++;
	}
	int ans = 0;
	for (int i = 0; i < 2 * n; i++)
		ans += l[i] * r[n * 2 - i];
	printf("%d\n", ans);
	return 0;
}
