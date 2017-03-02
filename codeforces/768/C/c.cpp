#include <bits/stdc++.h>

using namespace std;

int n, k, x;
int cnt[2][1030];
int main() {
	freopen("c.in", "r", stdin);
	scanf("%d %d %d", &n, &k, &x);
	for (int i = 1, a; i <= n; i++) {
		scanf("%d", &a);
		cnt[0][a]++;
	}
	for (int f = 1; f <= k; f++) {
		int sum = 0;
		memset(cnt[f & 1], 0, sizeof(cnt[f & 1]));
		for (int i = 0; i <= 1023; i++) {
			cnt[f & 1][i] += cnt[f & 1 ^ 1][i];
			if (sum & 1) {
				cnt[f & 1][i ^ x] += cnt[f & 1 ^ 1][i] >> 1;
				cnt[f & 1][i] -= cnt[f & 1 ^ 1][i] >> 1;
			} else {
				cnt[f & 1][i ^ x] += cnt[f & 1 ^ 1][i] + 1 >> 1;
				cnt[f & 1][i] -= cnt[f & 1 ^ 1][i] + 1 >> 1;
			}


			sum += cnt[f & 1 ^ 1][i];
		}
	}
	int mx = 0, mi = 0x3f3f3f3f;
	for (int i = 0; i <= 1023; i++)
		if (cnt[k & 1][i]) mx = i, mi = min(mi, i);
	cout << mx << ' ' << mi << endl;

	return 0;
}
