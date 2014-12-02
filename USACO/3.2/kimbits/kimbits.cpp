/*
ID:shijiey1
PROB:kimbits
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

long long n, l, i;
long long c[35][35];
long long dp[35][35];
int main() {
	freopen("kimbits.in", "r", stdin);
	freopen("kimbits.out", "w", stdout);
	scanf("%lld %lld %lld", &n, &l, &i);
	for (int j = 0; j <= n; j++) {
		c[j][0] = dp[0][j] = 1;
	}
	for (int j = 1; j <= n; j++) {
		for (int k = 1; k <= j; k++) {
			c[j][k] = c[j - 1][k] + c[j - 1][k - 1];
		}
	}
	for (int j = 1; j <= n; j++) {
		dp[j][0] = 1;
		for (int k = 1; k <= n; k++)
			dp[j][k] = dp[j][k-1] + c[j][k];
	}
	for (int k = n; k >= 1; k--) {
		if (dp[k - 1][l] < i) {
			cout << '1';
			i -= dp[k - 1][l];
			l--;
		} else {
			cout << '0';
		}
	}
	cout << endl;
	return 0;
}
