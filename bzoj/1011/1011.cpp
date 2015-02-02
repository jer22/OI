#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

#define MAXN 100005

using namespace std;

int n;
double a;
double m[MAXN];
double sum[MAXN];
double ans[MAXN];
int main() {
	freopen("1011.in", "r", stdin);
	scanf("%d %lf", &n, &a);
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &m[i]);
		sum[i] = sum[i - 1] + m[i];
	}
	for (int i = 1; i <= min(2000, n); i++) {
		int k = a * i;
		if(fabs((double)(k + 1) / a - i) < 1e-7)  k++;
		for (int j = 1; j <= k; j++) {
			ans[i] += m[i] * m[j] / double(i - j);
		}
	}
	for (int i = 2001; i <= n; i++) {
		int k = a * i;
		int t = k + 1 >> 1;
		ans[i] = sum[k] * m[i] / double(i - t);
	}
	for (int i = 1; i <= n; i++)
		printf("%lf\n", ans[i]);
	return 0;
}
