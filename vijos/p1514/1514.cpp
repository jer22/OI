#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
int arr[200010];
int maxnum[200010][20];
void init() {
	for (int j = 1; j <= 18; j++) {
		for (int i = 1; i <= n; i++) {
			if (i + (1 << j) - 1 <= n) {
				maxnum[i][j] = max(maxnum[i][j - 1], maxnum[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
}

int main() {
	freopen("1514.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		maxnum[i][0] = arr[i];
	}
	init();
	scanf("%d", &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		int k = log(b - a + 1) / log(2);
		int ans = max(maxnum[a][k], maxnum[b - (1 << k) + 1][k]);
		printf("%d\n", ans);
	}

	return 0;
}
