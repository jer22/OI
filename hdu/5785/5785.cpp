#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
const long long MOD = 1000000007ll;

char s[MAXN];
int cnt, last;
int tr[MAXN][26], fa[MAXN], len[MAXN], num[MAXN];
int pos[MAXN];
int sum[MAXN];
void extend(int c, int n) {
	int p = last;
	while (s[n - len[p] - 1] != s[n]) p = fa[p];
	if (!tr[p][c]) {
		int now = ++cnt, k = fa[p];
		len[now] = len[p] + 2;
		while (s[n - len[k] - 1] != s[n]) k = fa[k];
		fa[now] = tr[k][c];
		num[now] = num[fa[now]] + 1;
		sum[now] = (sum[fa[now]] + len[now]) % 1000000007;
		tr[p][c] = now;
	}
	last = tr[p][c];
	pos[n] = last;
}

void build(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = len[i] = pos[i] = num[i] = sum[i] = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j < 26; j++)
			tr[i][j] = 0;
	fa[0] = fa[1] = 1;
	cnt = 1;
	len[1] = -1;
	last = 0;
	for (int i = 0; i < n; i++)
		extend(s[i] - 'a', i);
}

int f[MAXN];
int main() {
	freopen("5785.in", "r", stdin);
	while (~scanf("%s", s)) {
		int n = strlen(s);
		build(n);

		for (int j = 0; j < n - 1; j++) {
			int posa = pos[j];
			long long x = ((long long)(j + 2) * num[posa] % MOD - sum[posa] + MOD) % MOD;
			f[j] = x;
		}
		for (int i = 0; i < n / 2; i++)
			swap(s[i], s[n - i - 1]);
		build(n);
		long long ans = 0;
		for (int j = 0; j < n - 1; j++) {
			int posb = pos[n - j - 2];
			long long x = ((long long)f[j] * (((long long)(j + 1) * num[posb] % MOD + sum[posb]) % MOD)) % MOD;
			(ans += x) %= MOD;
		}
		printf("%lld\n", ans);
	}

	
	return 0;
}
