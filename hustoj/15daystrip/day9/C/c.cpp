#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MOD = 1000000007;

int p[100005], ppns[100005];
void init() {
	p[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		int j = 1;
		while (1) {
			int pp = i - (j * (3 * j - 1)) / 2;
			int b = i - (j * (3 * j + 1)) / 2;
			if (pp < 0 && b < 0) break;
			int c = ((j & 1) << 1) - 1;

			if (pp >= 0) p[i] += c * p[pp];
			p[i] %= MOD;
			if (b >= 0) p[i] += c * p[b];
			p[i] %= MOD;
			j++;
		}
		p[i] += MOD;
		p[i] %= MOD;
	}
}

int getppns(int n, int lim) {
	int ppns = p[n];
	int j = 1;
	while (1) {
		int pp = n - lim * ((j * (3 * j - 1)) / 2);
		int b = n - lim * ((j * (3 * j + 1)) / 2);
		if (pp < 0 && b < 0) break;
		int c = ((j & 1) << 1) - 1;
		if (pp >= 0) ppns -= c * p[pp];
		ppns %= MOD;
		if (b >= 0) ppns -= c * p[b];
		ppns %= MOD;
		j++;
	}
	ppns += MOD;
	ppns %= MOD;
	return ppns;
}

int T, n, lim;
int main() {
	freopen("c.in", "r", stdin);
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &lim);
		int ppns = getppns(n, lim);
		printf("%d\n", ppns);
	}


	return 0;
}
