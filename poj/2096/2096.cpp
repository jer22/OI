#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, s;
double dp[1005][1005];
int main() {
	freopen("2096.in", "r", stdin);
	cin >> n >> s;
	for (int i = n; i >= 0; i--) {
		for (int j = s; j >= 0; j--) {
			if (i == n && j == s) continue;
			dp[i][j] = (i * (s - j) * dp[i][j + 1]
				+ (n - i) * j * dp[i + 1][j]
				+ (n - i) * (s - j) * dp[i + 1][j + 1]
				+ n * s) / (n * s - i * j);
		}
	}
	printf("%.4lf\n", dp[0][0]);


	return 0;
}
