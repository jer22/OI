#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int val[55], lim[55];
int c[2][250005];

int main() {
	freopen("d.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (n < 0) break;
		int sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &val[i], &lim[i]);
			sum += val[i] * lim[i];
		}
		memset(c, 0, sizeof(c));
		for (int i = 0; i <= lim[0]; i++)
			c[0][i * val[0]] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j <= sum >> 1; j++) {
				for (int k = 0; k <= lim[i] && k * val[i] + j <= sum >> 1; k++) {
					c[i & 1][j + k * val[i]] += c[!(i & 1)][j];
				}
			}
		}
		for (int i = sum / 2; i >= 0; i--) {
			if (c[(n - 1) & 1][i]) {
				printf("%d %d\n", sum - i, i);
				break;
			}
		}

	}


	return 0;
}
