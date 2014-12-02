#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int arr[1010][1010];
int transX[1010];
int transY[1010];
int main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	memset(arr, 0, sizeof(arr));
	memset(transX, 0, sizeof(transX));
	memset(transY, 0, sizeof(transY));
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	char c = getchar();
	int x, y;
	for (int i = 0; i < m; i++) {
		scanf("%c %d %d\n", &c, &x, &y);
		if (c == 'Q') {
			printf("%d\n", arr[x][y] ^ ((transX[x] + transY[y]) % 2));
		}
		if (c == 'T') {
			transX[x]++;
			transY[y]++;
		}
	}
	return 0;
}
