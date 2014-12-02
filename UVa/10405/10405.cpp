#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string a, b;
int dp[1010][1010];
int main() {
	freopen("10405.in", "r", stdin);
	while (getline(cin, a) && getline(cin, b)) {
		memset(dp, 0, sizeof(dp));
		int la = a.size();
		int lb = b.size();
		for (int i = 1; i <= la; i++) {
			for (int j = 1; j <= lb; j++) {
				if (a[i - 1] == b[j - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
				else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		printf("%d\n", dp[la][lb]);
	}

	return 0;
}
