#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 500005;

int T, n;
int divs[MAXN];
int cnt[MAXN];
bool pri[MAXN];
int p[MAXN], num = 0, tot = 0;

long long power(long long a, long long b) {
	long long ans = 1;
	long long base = a;
	while (b) {
		if (b & 1)
			ans = ans * base;
		base = base * base;
		b >>= 1;
	}
	return ans;
}

void init() {
	for (int i = 2; i < MAXN; i++) {
		if (pri[i]) continue;
		for (int j = i + i; j < MAXN; j += i)
			pri[j] = 1;
	}
	for (int i = 2; i < MAXN; i++)
		if (!pri[i]) p[num++] = i;

}

void getDiv() {
	int t = n;
	tot = 0;
	int idx = 0;
	while (t > 1) {
		// cout << t << endl;
		if (!(t % p[idx])) {
			cnt[tot] = 0;
			divs[tot] = p[idx];
			while (!(t % p[idx])) {
				t /= p[idx];
				cnt[tot]++;
			}
			tot++;
		}
		idx++;
	}
}

int main() {
	freopen("1215.in", "r", stdin);
	init();
	cin >> T;
	while (T--) {
		scanf("%d", &n);
		getDiv();
		long long ans = 1;
		for (int i = 0; i < tot; i++) {
			long long temp = 0;
			for (int j = 0; j <= cnt[i]; j++)
				temp += power((long long)divs[i], (long long)j);
			ans *= temp;
		}
		printf("%lld\n", ans - n);
	}

	return 0;
}
