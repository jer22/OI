#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

long long bit9[21], bit10[21];
long long l, r;
int K;
long long dp[21][10];

int digs[21], num;
long long solve(int dep) {
	

}

int main() {
	freopen("1007.in", "r", stdin);
	bit9[0] = bit10[0] = 1;
	for (int i = 1; i < 20; i++) {
		bit9[i] = bit9[i - 1] * 9;
		bit10[i] = bit10[i - 1] * 10;
	}
	while (~scanf("%lld %lld %d", &l, &r, &K)) {
		memset(dp, 0, sizeof(dp));
		solve(l - 1);

	}



	return 0;
}
