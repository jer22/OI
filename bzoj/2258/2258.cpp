#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const long long MOD = 1000000007;

int m;
char str[MAXN];
long long has[MAXN], fac[MAXN];
int id[MAXN];

void inithash() {
	int n = strlen(str + 1);
	for (int i = 1; i <= n; i++)
		has[i] = (has[i - 1] * 131 + str[i]) % MOD;
}
long long gethash(int a, int len) {
	int b = a + len - 1;
	long long tmp = has[a - 1] * fac[len] % MOD;
	return (has[b] - tmp + MOD) % MOD;
}

int solve(int a, int b) {
	int n = strlen(str + 1);
	int l = 1, r = n - b + 1;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (gethash(a, mid) == gethash(b, mid)) l = mid;
		else r = mid - 1;
	}
	if (gethash(a, l) == gethash(b, l)) return l;
	return 0;
}

int main() {
	freopen("2258.in", "r", stdin);
	scanf("%s", str + 1);
	int t = strlen(str + 1);
	fac[0] = 1;
	for (int i = 1; i < 200000; i++) {
		fac[i] = fac[i - 1] * 131 % MOD;
		id[i] = i;
	}
	inithash();
	scanf("%d", &m);
	int a, b;
	char c[3], op[3];
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		// cout << op << endl;
		if (op[0] == 'I') {
			scanf("%s %d", c, &a);
			int n = strlen(str + 1);
			if (a > n) a = n + 1;
			for (int j = n + 1; j > a; j--)
				str[j] = str[j - 1];
			for (int i = 1; i <= t; i++)
				if (id[i] >= a) id[i]++;
			str[a] = c[0];
			inithash();
		} else {
			scanf("%d %d", &a, &b);
			if (a > b) swap(a, b);
			printf("%d\n", solve(id[a], id[b]));
		}
	}

	return 0;
}
