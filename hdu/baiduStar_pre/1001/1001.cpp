#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 1000005;
const long long MOD = 1000000007;

int T, n;
long long f[MAXN];
int main() {
	freopen("1001.in", "r", stdin);
	f[1] = 1;
	f[2] = 2;
	for (int i = 3; i <= 1000000; i++) {
		f[i] = (i - 1) * f[i - 2] % MOD;
		f[i] += f[i - 1];
		f[i] %= MOD;
	}
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d", &n);
		printf("Case #%d:\n", cas++);
		cout << f[n] << endl;
	}

	return 0;
}
