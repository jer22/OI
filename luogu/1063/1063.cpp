#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int front[110];
int rear[110];
int dp[110][110];
int main( void ) {
	freopen("1063.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &front[i]);
	}
	for (int i = 0; i < n; i++) {
		rear[i] = front[(i + 1) % n];
	}
	for (int j = 1; j < n; j++) {
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < j; k++) {
				dp[i][j] = max(dp[i][j],
					dp[i][k] + dp[(i + k + 1) % n][j - k - 1]
					+ front[i] * rear[(i + k) % n] * rear[(i + j) % n]);
			}
		}
	}
	int maxval = 0;
		for (int i = 0; i < n; i++) {
			maxval = max(maxval, dp[i][n - 1]);
		}
	printf("%d", maxval);
	return 0;
}
