/*
ID:shijiey1
PROG:fence6
LANG:C++
*/

/*
将篱笆看作点，两段连接的篱笆之间连边，权值为两篱笆长度之和。
floyd最小环，然后结果除以2就是答案。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int edges[105][105];
int dist[105][105];
vector<int> lef[105];
vector<int> rig[105];
int len[105];
void addEdge(int from, int to, int value) {
	edges[from][to] = value;
}

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int n;
int main() {
	freopen("fence6.in", "r", stdin);
	freopen("fence6.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			edges[i][j] = INF;
		}
	}
	int s, ls, n1s, n2s;
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &s, &ls, &n1s, &n2s);
		len[s] = ls;
		int t;
		for (int j = 0; j < n1s; j++) {
			scanf("%d", &t);
			lef[s].push_back(t);
		}
		for (int j = 0; j < n2s; j++) {
			scanf("%d", &t);
			rig[s].push_back(t);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < lef[i].size(); j++)
			addEdge(i, lef[i][j], len[i] + len[lef[i][j]]);
		for (int j = 0; j < rig[i].size(); j++)
			addEdge(i, rig[i][j], len[i] + len[rig[i][j]]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = edges[i][j];
		}
	}
	int mincircle = INF;
	for (int k = 1; k <= n; k++) {
		for (int i = 0; i < lef[k].size(); i++) {
			int ii = lef[k][i];
			if (ii >= k) continue;
			for (int j = 0; j < rig[k].size(); j++) {
				int jj = rig[k][j];
				if (jj >= k) continue;
				mincircle = min(mincircle, dist[ii][jj] + edges[jj][k] + edges[k][ii]);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	printf("%d\n", mincircle >> 1);

	return 0;
}
