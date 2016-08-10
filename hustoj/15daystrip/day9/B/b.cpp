#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MOD = 1000000007;

int T, n;
int p[100005];
void init() {
	p[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		int j = 1;
		while (1) {
			int a = i - (j * (3 * j - 1)) / 2;
			int b = i - (j * (3 * j + 1)) / 2;
			if (a < 0 && b < 0) break;
			int c = ((j & 1) << 1) - 1;

			if (a >= 0) p[i] += c * p[a];
			p[i] %= MOD;
			if (b >= 0) p[i] += c * p[b];
			p[i] %= MOD;
			j++;
		}
		p[i] += MOD;
		p[i] %= MOD;
	}
}

int main() {
	freopen("b.in", "r", stdin);
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%d\n", p[n]);
	}


	return 0;
}
