#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, G, L;
int divs[10000005];
int cnt[10000005];
bool pri[10000005];
int p[10000005], num = 0, tot = 0;
void init() {
	for (int i = 2; i < 10000005; i++) {
		if (pri[i]) continue;
		for (int j = i + i; j < 10000005; j += i)
			pri[j] = 1;
	}
	for (int i = 2; i < 10000005; i++)
		if (!pri[i]) p[num++] = i;

}

void getDiv() {
	int t = L;
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
	freopen("4497.in", "r", stdin);
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &G, &L);
		if (L % G || !G) {
			cout << 0 << endl;
			continue;
		}
		L /= G;
		getDiv();
		long long ans = 1;
		for (int i = 0; i < tot; i++) {
			ans *= cnt[i];
			ans *= 6;
		}
		cout << ans << endl;

	}


	return 0;
}
