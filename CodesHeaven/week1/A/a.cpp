#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const long long MOD = 1000000007ll;

int arr[MAXN][MAXN];
int deg[MAXN];
long long kir[MAXN][MAXN];

void getkir(int n, int ban) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			kir[i][j] = 0;
	}
	for (int i = 1; i <= n; i++) if (i != ban)
		if (arr[ban][i]) deg[i]--;
	for (int i = 1, k = 1; i <= n; i++) {
		if (i == ban) continue;

		for (int j = 1, l = 1; j <= n; j++) {
			if (j == ban) continue;
			if (i == j) kir[k][l] = deg[i];
			else if (arr[i][j]) kir[k][l] = -1;
			l++;
		}
		k++;
	}
	for (int i = 1; i <= n; i++) if (i != ban)
		if (arr[ban][i]) deg[i]++;
}

long long cal(int n) {
	long long ret=1ll;
	for(int i=2; i<=n; i++)
	{
		for(int j=i+1; j<=n; j++)
			while(kir[j][i])
			{
				long long t=kir[i][i]/kir[j][i];
				for(int k=i; k<=n; k++)
					kir[i][k]=(((kir[i][k]-kir[j][k]*t)%MOD)+MOD)%MOD;
				for(int k=i; k<=n; k++)
					swap(kir[i][k],kir[j][k]);
				ret=-ret;
			}
		if(kir[i][i]==0ll)
			return 0;
	}
	for (int i = 2; i <= n; i++)
		ret = (ret * kir[i][i]) % MOD;
	return (ret % MOD + MOD) % MOD;
}

int T, n, m;
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			deg[i] = 0;
			for (int j = 1; j <= n; j++)
				arr[i][j] = 0;
		}
		for (int i = 0, a, b; i < m; i++) {
			scanf("%d %d", &a, &b);
			arr[a][b] = arr[b][a] = 1;
			deg[a]++, deg[b]++;
		}
		long long ans = (long long)(1ll + n) * n / 2ll;
		ans %= MOD;
		getkir(n, 0);
		long long sum = cal(n);
		ans = (ans * sum) % MOD;
		for (int i = 1; i <= n; i++) {
			getkir(n, i);
			long long fuck = cal(n - 1);
			// cout << fuck << endl;
			ans -= (((fuck * deg[i]) % MOD) * i) % MOD;
			while (ans < 0) ans += MOD;
			ans %= MOD;
		}
		printf("%lld\n", ans % MOD);
	}


	return 0;
}
