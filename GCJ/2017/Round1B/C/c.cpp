#include <bits/stdc++.h>

#define r(i) for (int i = 1; i <= n; i++)

using namespace std;

const int MAXN = 105;
const int INF = 0x3f3f3f3f;
const double DINF = 1e30;

int T;
int mxds[MAXN], spd[MAXN];
int dist[MAXN][MAXN];
double tim[MAXN][MAXN];
int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		int n, q;
		printf("Case #%d: ", cas);
		scanf("%d %d", &n, &q);
		r(i) {
			scanf("%d %d", &mxds[i], &spd[i]);
		}
		r(i) { r(j) {
				scanf("%d", &dist[i][j]);
				if (dist[i][j] == -1) dist[i][j] = INF;
			}
		}
		r(k) r(i) r(j)
			dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
		r(i) { r(j) {
			if (dist[i][j] <= mxds[i]) {
				tim[i][j] = double(dist[i][j]) / spd[i];
			}
			else tim[i][j] = DINF;
		}}
		r(k) { r(i) { r(j) {
			// if (dist[i][k] <= mxds[i] && dist[k][j] <= mxds[k])
				tim[i][j] = min(tim[i][j], tim[i][k] + tim[k][j]);
		}}}
		for (int i = 1, a, b; i <= q; i++) {
			scanf("%d %d", &a, &b);
			printf("%.10lf%c", tim[a][b], " \n"[i == q]);
		}
	}


	return 0;
}
