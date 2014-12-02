#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int arr[1010][1010];
int canGo[1010][1010];
int main() {
	freopen("1176.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		canGo[a][b] = 1;
	}
	arr[1][1] = 1;
	canGo[1][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!canGo[i][j])
				arr[i][j] = (arr[i - 1][j] + arr[i][j - 1]) % 100003;
		}
	}
	printf("%d\n", arr[n][n] % 100003);
	return 0;
}
