#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int T;
int K;
long long x;
long long p[11][11];

long long cal(long long num, int k) {
	long long ans = 0;
	while (num) {
		ans += p[num % 10][k];
		num /= 10;
	}
	return ans;
}

long long tmp[100005];
long long cnt[11][100005];
vector<long long> num[11];
void init() {
	for (int i = 0; i <= 9; i++) {
		p[i][0] = 1ll;
		for (int j = 1; j <= 9; j++)
			p[i][j] = p[i][j - 1] * i;
	}
	for (int k = 1; k <= 9; k++) {
		for (int i = 0; i < 100000; i++) {
			tmp[i] = cal(i, k) - (long long)i * 100000;
		}
		sort(tmp, tmp + 100000);
		int pre = -1;
		for (int i = 0; i < 100000; i++) {
			if (!i || tmp[i] != tmp[i - 1]) {
				pre++;
				cnt[k][pre] = 1;
				num[k].push_back(tmp[i]);
			} else cnt[k][pre]++;
		}
	}
}

int main() {
	// freopen("5936.in", "r", stdin);
	init();
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%lld %d", &x, &K);
		long long ans = 0;
		for (int i = 0; i < 100000; i++) {
			long long t = x - cal(i, K) + (long long)i;

			int l = 0, r = num[K].size() - 1;
			while (l < r) {
				int m = l + r >> 1;
				if (num[K][m] < t) l = m + 1;
				else r = m;
			}
			if (num[K][l] == t) ans += cnt[K][l];
		}
		if (!x) ans--;
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}
