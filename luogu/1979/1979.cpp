#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 35

using namespace std;

int n, m, q;
int arr[MAXN][MAXN];
int main() {
	freopen("1979.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	



	// 执行查询
	int ex, ey, sx, sy, tx, ty;
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d %d %d %d", &ex, &ey, &sx, &sy, &tx, &ty);
	}
	return 0;
}
