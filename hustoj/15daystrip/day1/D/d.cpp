#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n, l;
char s[305];
string w[605];
int dp[305];
int main() {
	freopen("d.in", "r", stdin);
	cin >> n >> l;
	scanf("%s", s + 1);
	for (int i = 0; i < n; i++)
		cin >> w[i];
	for (int i = l; i >= 1; i--) {
		dp[i] = dp[i + 1] + 1;
		for (int j = 0; j < n; j++) {
			if (s[i] != w[j][0]) continue;
			int t = i + 1;
			int idx = 1;
			while (t <= l) {
				if (s[t] == w[j][idx]) idx++;
				if (idx == (int)w[j].size()) break;
				t++;
			}
			if (t <= l) {
				dp[i] = min(dp[i], dp[t + 1] + t - i + 1 - (int)w[j].length());
			}
		}
	}
	cout << dp[1] << endl;


	return 0;
}
