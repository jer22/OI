#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;
int mob[MAXN];
int sum[MAXN];
void getMob() {
	for (int i = 1; i <= 50000; i++) {
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= 50000; j += i)
			mob[j] += delta;
	}
	for (int i = 1; i <= 50000; i++)
		sum[i] = sum[i - 1] + mob[i];
}
int main() {
	freopen("1101.in", "r", stdin);
	int a, b, d;
	int T;
	getMob();
	scanf("%d", &T);

	while (T--) {
		scanf("%d %d %d", &a, &b, &d);
		a /= d, b /= d;
		if (a > b) swap(a, b);
		int ans = 0;
		for (int i = 1, pos; i <= a; i = pos + 1) {
			pos = min(a / (a / i), b / (b / i));
			ans += (sum[pos] - sum[i - 1]) * (a / i) * (b / i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
