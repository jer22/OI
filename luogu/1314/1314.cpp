#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAXN 200010
#define INF ~0llu >> 1

using namespace std;

int n, m;
long long S;
int a[MAXN];
long long b[MAXN];
int weight[MAXN];
int value[MAXN];
int start[MAXN];
int end[MAXN];
long long ans = INF;

long long getResult(int w) {
	long long Y = 0;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	for (int i = 1; i <= n; i++) {
		a[i] = a[i - 1];
		b[i] = b[i - 1];
		// printf("|%d %d|\n", weight[i], value[i]);
		if (w <= weight[i]) {
			a[i]++;
			b[i] += value[i];
		}
	}
	for (int i = 1; i <= m; i++) {
		Y += (a[end[i]] - a[start[i] - 1])
			* (b[end[i]] - b[start[i] - 1]);
	}
	return Y;
}

int main() {
	freopen("1314.in", "r", stdin);
	scanf("%d %d %lld", &n, &m, &S);
	int minW = 0x3f3f3f3f;
	int maxW = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &weight[i], &value[i]);
		minW = min(minW, weight[i]);
		maxW = max(maxW, weight[i]);
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &start[i], &end[i]);
	}
	while (minW < maxW) {
		long long m = (minW + maxW) >> 1;
		long long c = getResult(m + 1);
		ans = min(ans, abs(c - S));
		if (c <= S) {
			maxW = m;
		} else {
			minW = m + 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
