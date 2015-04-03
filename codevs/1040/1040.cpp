#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

string str = "";
int T, p, k;
int m;
string dict[8];
int cnt[205][205];
int dp[205][40];
int main() {
	freopen("1040.in", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> p >> k;
		string t;
		while (p--) {
			cin >> t;
			str += t;
		}
		cin >> m;
		for (int i = 0; i < m; i++)
			cin >> dict[i];
		memset(cnt, 0, sizeof(cnt));
		for (int j = str.size() - 1; j >= 0; j--) {
			for (int i = j; i >= 0; i--) {
				bool flag = false;
				for (int l = 0; l < m; l++) {
					if (str.find(dict[l], i) == i && dict[l].size() <= j - i + 1) {
						flag = true;
						break;
					}
				}
				if (flag) cnt[i][j] = cnt[i + 1][j] + 1;
				else cnt[i][j] = cnt[i + 1][j];
			}
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < str.size(); i++)
			dp[i][1] = cnt[0][i];
		for (int l = 2; l <= k; l++) {
			for (int i = l - 1; i < str.size(); i++) {
				for (int j = i - 1; j >= l - 1; j--)
					dp[i][l] = max(dp[i][l], dp[j][l - 1] + cnt[j + 1][i]);
			}
		}
		cout << dp[str.size() - 1][k] << endl;
	}


	return 0;
}
