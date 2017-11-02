#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>

using namespace std;

int vis[100][100], mark[100];

int main()
{
	freopen("sample.in", "w", stdout);

	int T = 25;

	printf("%d\n", T);

	while (T--) {
		memset(vis, 0, sizeof vis);
		memset(mark, 0, sizeof mark);

		int n = 50, m = 240, k = 8;

		printf("%d %d %d\n", n, m, k);

		for (int i = 1; i <= m; i++) {
			int u = rand() % n + 1;
			int v = rand() % n + 1;

			while (vis[u][v]) {
				u = rand() % n + 1;
				v = rand() % n + 1;
			}

			vis[u][v] = vis[v][u] = 1;
			int w = rand() % 10000;

			printf("%d %d %d\n", u, v, w);
		}

		for (int i = 1; i <= k; i++) {
			int p = rand() % n + 1;

			while (mark[p])
				p = rand() % n + 1;
			mark[p] = 1;

			int t1 = rand() % 10000;
			int t2 = rand() % 10000;
			if (t1 < t2)
				swap(t1, t2);

			printf("%d %d %d ", p, t1, t2);

			int s = rand() % n + 1;

			printf("%d ", s);

			for (int j = 1; j <= s; j++)
				printf("%d%c", rand() % n + 1, j == s ? 10 : 32);
		}
	}

	return 0;
}
