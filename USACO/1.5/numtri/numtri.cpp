/*
ID:shijiey1
PROG:numtri
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[1010][1010];
int dp[1010][1010];
int main() {
	freopen("numtri.in", "r", stdin);
	freopen("numtri.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			dp[i][j] = max(dp[i + 1][j] + arr[i][j], dp[i + 1][j + 1] + arr[i][j]);
		}
	}
	printf("%d\n", dp[0][0]);
	return 0;
}
