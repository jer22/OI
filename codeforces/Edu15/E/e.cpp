#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
long long k;
int to[MAXN][55];
long long val[MAXN][55];
long long mi[MAXN][55];
long long sum[MAXN], smi[MAXN];
int idx[MAXN];

int main() {
	freopen("e.in", "r", stdin);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &to[i][0]);
		to[i][0]++;
		idx[i] = i;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &val[i][0]);
		mi[i][0] = val[i][0];
	}
	memset(smi, 0x3f, sizeof(smi));
	int j = 0;
	long long t = k;
	while (k) {
		for (int i = 1; i <= n; i++) {
			val[i][j + 1] = val[i][j] + val[to[i][j]][j];
			mi[i][j + 1] = min(mi[i][j], mi[to[i][j]][j]);
			to[i][j + 1] = to[to[i][j]][j];
		}
		j++;
		k >>= 1;
	}
	j--;
	k = t;

	while (k) {
		while ((1ll << j) > k) j--;
		for (int i = 1; i <= n; i++) {
			sum[i] += val[idx[i]][j];
			smi[i] = min(smi[i], mi[idx[i]][j]);
			idx[i] = to[idx[i]][j];
		}
		k -= (1ll << j);
	}
	for (int i = 1; i <= n; i++) {
		cout << sum[i] << ' ' << smi[i] << endl;
	}

	return 0;
}
