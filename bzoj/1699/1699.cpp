#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 50005;

int n, q;
int mi[MAXN][20];
int mx[MAXN][20];

void RMQ() {
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= n; i++) {
			if (i + (1 << j) - 1 <= n) {
				mi[i][j] = min(mi[i][j - 1], mi[i + (1 << j - 1)][j - 1]);
				mx[i][j] = max(mx[i][j - 1], mx[i + (1 << j - 1)][j - 1]);
			}
		}
	}
}

int getmax(int a, int b) {
	int k = log(b - a + 1) / log(2);
	return max(mx[a][k], mx[b - (1 << k) + 1][k]);
}

int getmin(int a, int b) {
	int k = log(b - a + 1) / log(2);
	return min(mi[a][k], mi[b - (1 << k) + 1][k]);
}

int main() {
	freopen("1699.in", "r", stdin);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &mi[i][0]);
		mx[i][0] = mi[i][0];
	}
	RMQ();
	int a, b;
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", getmax(a, b) - getmin(a, b));
	}

	return 0;
}
