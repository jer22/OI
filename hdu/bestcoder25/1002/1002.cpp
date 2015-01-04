#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;

int n, m;
long long Bin[55];
long long C[55][55];
long long ans[55][55];
void init() {
	Bin[0] = 1;
	for (int i = 1; i <= 51; i++)
		Bin[i] = Bin[i - 1] * 2;
	for (int i = 1; i <= 50; i++)
		C[i][0] = C[i][i] = 1;
	for (int i = 2; i <= 50; i++)
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
}

long long cal(int n, int m) {
	long long ans = 0;
	long long tt = -1;
	for (int j = 0; j < m; j++) {
		tt = -tt;
		long long pre = C[m][j];
		long long nex = Bin[m - j] - 1;
		nex %= MOD;
		long long k = 1;
		for (int i = 1; i <= n; i++) {
			k *= nex;
			k %= MOD;
		}
		ans += tt * pre * k;
		ans %= MOD;
	}
	ans = (ans + MOD) % MOD;
	return ans;
}

void work() {
	for (int i = 1; i <= 50; i++) {
		for (int j = 1; j <= i; j++) {
			ans[i][j] = ans[j][i] = cal(i, j);
		}
	}
}

int main() {
	freopen("1002.in", "r", stdin);
	init();
	work();
	while (~scanf("%d %d", &n, &m)) {
		if (!n || !m) cout << 1 << endl;
		else cout << ans[n][m] << endl;
	}
	

	return 0;
}
