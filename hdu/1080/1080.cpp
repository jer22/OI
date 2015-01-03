#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int T;
int len1, len2;
string s1, s2;
int arr[5][5] = {{5, -1, -2, -1, -3},
	{-1, 5, -3, -2, -4}, {-2, -3, 5, -2, -2},
	{-1, -2, -2, 5, -1}, {-3, -4, -2, -1, 0}};
map<char, int> let;
int dp[110][110];
int main() {
	freopen("1080.in", "r", stdin);
	scanf("%d", &T);
	let['A'] = 0;
	let['C'] = 1;
	let['G'] = 2;
	let['T'] = 3;
	let['-'] = 4;
	while (T--) {
		cin >> len1 >> s1 >> len2 >> s2;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= len1; i++)
            dp[i][0] = dp[i - 1][0] + arr[let['-']][let[s1[i - 1]]];
        for (int j = 1; j <= len2; j++)
            dp[0][j] = dp[0][j - 1] + arr[let['-']][let[s2[j - 1]]];
		for (int i = 1; i <= len1; i++) {
			for (int j = 1; j <= len2; j++) {
				char a = s1[i - 1];
				char b = s2[j - 1];
				dp[i][j] = max(dp[i - 1][j - 1] + arr[let[a]][let[b]], max(dp[i][j - 1] + arr[let['-']][let[b]], dp[i - 1][j] + arr[let[a]][let['-']]));
			}
		}
		cout << dp[len1][len2] << endl;
	}


	return 0;
}
