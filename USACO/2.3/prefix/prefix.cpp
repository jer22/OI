/*
ID:shijiey1
PROG:prefix
LANG:C++
*/

/*
用dp[i]表示第i位是否可行。
初始状态：dp[0]=1;
则如果dp[i]==1,则枚举每一个在集合p中的字符串p[j]，dp[i+strlen(p[j])]=1。
然后从右向左扫，遇到第一个可行的点输出。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

char p[210][20];
char s[200010];
int dp[200010];
int n = 0;
int main() {
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
	while (scanf("%s", p[n])) {
		if (p[n][0] != '.') n++;
		else break;
	}
	scanf("%s", s + 1);
	char t[80];
	while (~scanf("%s", t)) {
		strcpy(s + 1 + strlen(s + 1), t);
	}
	dp[0] = 1;
	int len = strlen(s + 1);
	for (int i = 1; i <= len; i++) {
		if (dp[i - 1]) {
			for (int j = 0; j < n; j++) {
				int lp = strlen(p[j]);
				int k = 0;
				for (int l = 0; k < lp && l <= len - i; k++, l++) {
					if (p[j][k] != s[i + l])
						break;
				}
				if (k == lp) {
					dp[i + lp - 1] = 1;
				}
			}
		}
	}
	for (int j = strlen(s + 1); j >= 0; j--) {
		if (dp[j]) {
			printf("%d\n", j);
			return 0;
		}
	}


	return 0;
}
