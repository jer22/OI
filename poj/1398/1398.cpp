#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int T, n, s;
int arr[105];
double c[105][105];

void init() {
	for (int j = 0; j < n; j++) {
		for (int i = 0; i + j < n; i++) {
			if (!j) c[i][i + j] = arr[i];
			else c[i][i + j] = (c[i + 1][i + j] - c[i][i + j - 1]) / j;
		}
	}
}

double calc(double x) {
	double ans = 0.0, t = 1.0;
	for (int i = 0; i < n; i++) {
		ans += c[0][i] * t;
		t *= (x - i - 1);
	}
	return ans;
}

int main() {
	freopen("1398.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &s);
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		init();
		for (int i = n + 1; i <= n + s; i++) {
			if (i != n + 1) printf(" ");
			printf("%d", (int)(calc(i) + 1e-8));
		}
		printf("\n");
	}


	return 0;
}
