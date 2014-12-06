/*
ID:shijiey1
LANG:C++
PROG:charrec
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

int n;
int font[30][30][30];
int data[1205][30];
int diff[30][30][1205];
int cost[1205][4];
int from[1205][4];
int dp[1205];
char letter[30] = " abcdefghijklmnopqrstuvwxyz";
int main() {
	freopen("font.in", "r", stdin);
	scanf("%d", &n), getchar();
	for (int i = 1; i <= 27; i++) {
		for (int j = 1; j <= 20; j++, getchar()) {
			for (int k = 1; k <= 20; k++) {
				font[i][j][k] = getchar();
			}
		}
	}
	freopen("charrec.in", "r", stdin);
	freopen("charrec.out", "w", stdout);
	scanf("%d", &n), getchar();
	for (int i = 1; i <= n; getchar(), i++)
		for (int j = 1; j <= 20; j++)
			data[i][j] = getchar();
	for (int i = 1; i <= 27; i++) {
		for (int j = 1; j <= 20; j++) {
			for (int k = 1; k <= n; k++) {
				diff[i][j][k] = 0;
				for (int p = 1; p <= 20; p++) {
					diff[i][j][k] += (data[k][p] != font[i][j][p]);
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		cost[i][1] = cost[i][2] = cost[i][3] = INF;
		if (i + 18 <= n) {
			for (int j = 1; j <= 27; j++) {
				int total = 0;
				for (int k = 2; k <= 20; k++) {
					total += diff[j][k][i + k - 2];
				}
				if (total < cost[i][1]) {
					cost[i][1] = total;
					from[i][1] = j;
				}
				for (int k = 2; k <= 20; k++) {
					total += diff[j][k - 1][i + k - 2];
					total -= diff[j][k][i + k - 2];
					if (total < cost[i][1]) {
						cost[i][1] = total;
						from[i][1] = j;
					}
				}
			}
		}
		if (i + 19 <= n) {
			for (int j = 1; j <= 27; j++) {
				int total = 0;
				for (int k = 1; k <= 20; k++) {
					total += diff[j][k][i + k - 1];
				}
				if (total < cost[i][2]) {
					cost[i][2] = total;
					from[i][2] = j;
				}
			}
		}
		if (i + 20 <= n) {
			for (int j = 1; j <= 27; j++) {
				int total = diff[j][1][i];
				for (int k = 2; k <= 20; k++) {
					total += diff[j][k][i + k];
				}
				if (total < cost[i][3]) {
					cost[i][3] = total;
					from[i][3] = j;
				}
				for (int k = 2; k <= 20; k++) {
					total += diff[j][k][i + k - 1];
					total -= diff[j][k][i + k];
					if (total < cost[i][3]) {
						cost[i][3] = total;
						from[i][3] = j;
					}
				}	
			}
		}
	}
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = INF;
	}
	int g[1205];
	memset(g, 0, sizeof(g));
	for (int i = 19; i <= n; i++) {
		if (i >= 19 && dp[i - 19] < INF && dp[i - 19] + cost[i - 18][1] < dp[i]) {
			dp[i] = dp[i - 19] + cost[i - 18][1];
			g[i] = 19;
		}
		if (i >= 20 && dp[i - 20] < INF && dp[i - 20] + cost[i - 19][2] < dp[i]) {
			dp[i] = dp[i - 20] + cost[i - 19][2];
			g[i] = 20;
		}
		if (i >= 21 && dp[i - 21] < INF && dp[i - 21] + cost[i - 20][3] < dp[i]) {
			dp[i] = dp[i - 21] + cost[i - 20][3];
			g[i] = 21;
		}
	}
	int ans[1205];
	int total = 0;
	for (int i = n; i; i -= g[i]) {
		ans[++total] = from[i - g[i] + 1][g[i] - 18];
	}
	for (int i = total; i; i--) {
		cout << letter[ans[i] - 1];
	}
	cout << endl;
	return 0;
}
