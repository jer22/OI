#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n;
double a[12][12];
double x[12][12];
void gauss() {
	for (int i = 1; i <= n - 1; i++) {
		int pos = i;
		for (int j = i + 1; j <= n; j++)
			if (abs(a[pos][i]) < abs(a[j][i])) pos = j;
		for (int j = 1; j <= n + 1; j++) swap(a[i][j], a[pos][j]);
		for (int j = i + 1; j <= n; j++) {
			double p = a[j][i] / a[i][i];
			for (int k = i; k <= n + 1; k++)
				a[j][k] -= p * a[i][k];
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = i + 1; j <= n; j++) a[i][n + 1] -= a[j][n + 1] * a[i][j];
		a[i][n + 1] /= a[i][i];
	}
}

int main() {
	freopen("1013.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lf", &x[i][j]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) a[i][j] = 2 * (x[i + 1][j] - x[i][j]);
		for (int j = 1; j <= n; j++) a[i][n + 1] += x[i + 1][j] * x[i + 1][j] - x[i][j] * x[i][j];
	}
	gauss();
	for (int i = 1; i <= n; i++) {
		if (i > 1) printf(" ");
		printf("%.3lf", a[i][n + 1]);
	}
	printf("\n");
	return 0;
}
