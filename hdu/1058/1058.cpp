#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int dp[6000];
int i = 1, j = 1, k = 1, l = 1;
void init() {
	dp[1] = 1;
	for (int n = 2; n <= 5842; n++) {
		int t;
		do {
			int a = dp[i] * 2;
			int b = dp[j] * 3;
			int c = dp[k] * 5;
			int d = dp[l] * 7;
			t = min(min(a, b), min(c, d));
			if (t == a) i++;
			else if (t == b) j++;
			else if (t == c) k++;
			else if (t == d) l++;
			// dp[n] = t;
		} while (t <= dp[n - 1]);
		dp[n] = t;
	}
}

int n;
int main() {
	freopen("1058.in", "r", stdin);
	init();
	char st[3] = "st";
	char nd[3] = "nd";
	char rd[3] = "rd";	
	while (~scanf("%d", &n) && n) {
		int a = n % 10;
		int b = n % 100;
		char now[3] = "th";
		if (a == 1 && b != 11) memcpy(now, st, sizeof(now));
		if (a == 2 && b != 12) memcpy(now, nd, sizeof(now));
		if (a == 3 && b != 13) memcpy(now, rd, sizeof(now));
		printf("The %d%s humble number is %d.\n", n, now, dp[n]);
	}

	return 0;
}
