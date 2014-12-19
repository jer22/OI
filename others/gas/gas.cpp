#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

double dist[55];
double cost[55];
double C, d2;
int n;
double far, half;
double dp[55];
int pre[55];
double ans = 0x3f3f3f3f;
int main() {
	freopen("gas.in", "r", stdin);
	double a, b, c, d;
	cin >> a >> C >> d2 >> dp[0];
	far = C * d2;
	half = c / 2;
	cin >> n;
	dist[n + 1] = a;
	for (int i = 1; i <= n; i++) {
		cin >> dist[i] >> cost[i];
	}
	n++;
	memset(pre, -1, sizeof(pre));
	for (int i = 1; i <= n; i++) dp[i] = 0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		if (dist[n] - dist[i] <= far) {
			if (dp[i] < ans) {
				ans = dp[i];	
				pre[n] = i;
			}
		}
		for (int j = i + 1; j < n; j++) {
			if (dist[j] - dist[i] > far) break;
			if ((dist[j] - dist[i]) / d2 < half && dist[j + 1] - dist[i] > far) {
				continue;
			}
			if (dp[j] > dp[i] + ((dist[j] - dist[i]) / d2) * cost[j] + 2) {
				dp[j] = dp[i] + ((dist[j] - dist[i]) / d2) * cost[j] + 2;	
				pre[j] = i;
			}
			
		}
	}
	cout << ans << endl;
	
	return 0;
}
