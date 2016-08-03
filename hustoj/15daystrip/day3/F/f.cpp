#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 1000005;

int n;
int p[MAXN], dp[MAXN];
int fir[MAXN], sec[MAXN];
int main() {
	freopen("f.in", "r", stdin);
	scanf("%d", &n);
	int x;
	int ret = 0;
	for (int i = 2; i <= n + 1; i++) {
		scanf("%d", &x);
		p[i] = x;
		dp[i] = 1;
		int now = i;
		while (now != 1) {

			int pa = p[now];
			if (dp[now] > fir[pa]) {
				sec[pa] = fir[pa];
				fir[pa] = dp[now];
			} else if (dp[now] > sec[pa]) {
				sec[pa] = dp[now];
			}

			int r = max(fir[pa], sec[pa] + 1);
			if (r == dp[pa]) break;
			dp[pa] = r;
			now = p[now];
		}


		if (i > 2) printf(" ");
		printf("%d", fir[1]);
	}
	printf("\n");


	return 0;
}
