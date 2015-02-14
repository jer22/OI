#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

long long n;
long long prime[105];
int cnt[105];
int tot = 0;
void init() {
	tot = 0;
	long long m = n;
	int k = sqrt(m);
	for (int i = 2; i <= k; i++) {
		if (!(m % i)) {
			while (!(m % i)) {
				cnt[tot]++;
				m /= i;
			}
			prime[tot++] = i;
		}
	}
	if (m != 1) {
		cnt[tot] = 1;
		prime[tot++] = m;
	}
}

int num = 0;
long long ans[105];

long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}

void dfs(int cur, long long x) {
	if (cur >= tot) {
		if (((n ^ x) < n) && gcd(n, n ^ x) == x) ans[num++] = (n ^ x);
		return;
	}
	for (int i = 0; i <= cnt[cur]; i++) {
		dfs(cur + 1, x);
		x *= prime[cur];
	}
}

int main() {
	freopen("1002.in", "r", stdin);
	int cas = 1;
	while (~scanf("%lld", &n)) {
		init();
		num = 0;
		dfs(0, 1);
		num--;
		sort(ans, ans + num);
		printf("Case #%d:\n", cas++);
		cout << num << endl;
		for (int i = 0; i < num; i++)
			cout << ans[i] << " \n"[i == num - 1];
	}


	return 0;
}
