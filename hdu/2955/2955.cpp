#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

double dp[11000];
int main() {
	freopen("2955.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		double p;
		int value[110];
		double prob[110];
		int sum = 0;
		scanf("%lf %d", &p, &n);
		double pp = 1 - p;
		for (int i = 1; i <= n; i++) {
			scanf("%d %lf", &value[i], &prob[i]);
			prob[i] = 1 - prob[i];
			sum += value[i];
		}
		for (int i = 0; i <= sum; i++) {
			dp[i] = -1;
		}
		dp[value[1]] = prob[1];
		dp[0] = 1;
		for (int i = 2; i <= n; i++) {
			for (int j = sum; j >= value[i]; j--) {
				if (dp[j - value[i]] != -1) {
					dp[j] = max(dp[j], dp[j - value[i]] * prob[i]);
				}

				if (dp[j] != -1){
					dp[j] = max(dp[j], dp[j - value[i]] * prob[i]);
				}
			}
		}
		for (int i = sum; i >= 0; i--) {
			if (dp[i] > pp) {
				printf("%d\n", i);
				break;
			}
		}
	}

	return 0;
}
