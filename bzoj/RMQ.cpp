#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAXN 1000

using namespace std;

int n;
int arr[MAXN];
int maxsum[MAXN][11];
int minsum[MAXN][11];

void RMQ() {
	for (int j = 1; j <= 10; j++) {
		for (int i = 1; i <= n; i++) {
			if (i + (1 << j) - 1 <= n) {
				maxsum[i][j] = max(maxsum[i][j - 1], maxsum[i + (1 << (j - 1))][j - 1]);
				minsum[i][j] = min(minsum[i][j - 1], minsum[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		maxsum[i][0] = arr[i];
		minsum[i][0] = arr[i];
	}
	RMQ();
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 0; i + (1 << j) - 1 <= n; j++) {
	// 		printf("%d ", maxsum[i][j]);
	// 	}
	// 	printf("\n");
	// }
	int a, b;
	scanf("%d %d", &a, &b);
	int k = log(b - a + 1) / log(2);
	int minAns = min(minsum[a][k], minsum[b - (1 << k) + 1][k]);
	int maxAns = max(maxsum[a][k], maxsum[b - (1 << k) + 1][k]);
	printf("%d %d\n", minAns, maxAns);
	return 0;
}
