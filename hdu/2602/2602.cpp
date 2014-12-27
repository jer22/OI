#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n, v;
int value[1005];
int volum[1005];
int dp[1005];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &v);
		for (int i = 1; i <= n; i++)
			cin >> value[i];
		for (int i = 1; i <= n; i++)
			cin >> volum[i];
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			for (int j = v; j >= volum[i]; j--) {
				dp[j] = max(dp[j], dp[j - volum[i]] + value[i]);
			}
		}
		cout << dp[v] << endl;
	}
	return 0;
}
