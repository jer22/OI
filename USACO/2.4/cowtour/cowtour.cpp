/*
ID:shijiey1
PROG:cowtour
LANG:C++
*/

/*
注意题目中的直径并不是指距离最远的两点的距离，而是最短路最长两点的最短路。
用map[i][j]表示两点之间的最短路。
读入时初始化map，如果两点之间有边则map[i][j]=dist(i, j)否则map[i][j]=INF.
然后用一次floyd算出任意两点最短路。
mmax[i]表示从节点i出发，能到达的最远的节点的路程。
对于每一个不联通的i，j，将他俩接通，此时直径为mmax[i]+mmax[j]+dist(i,j).
枚举每一个不联通的i，j，计算直径统计最大值。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define INF 0x3f3f3f3f

using namespace std;

int n;
int x[155], y[155];
double map[155][155];
double mmax[155];
double res = INF;
double dist(int a, int b) {
	return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}

int main() {
	freopen("cowtour.in", "r", stdin);
	freopen("cowtour.out", "w", stdout);
	memset(mmax, 0, sizeof(mmax));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d\n", &x[i], &y[i]);
	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%c", &c);
			if (c == '1') map[i][j] = dist(i, j);
			else map[i][j] = INF;
			if (i == j) map[i][j] = 0;
		}
		getchar();
	}

	
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				map[i][j] = min(map[i][j], map[i][k] + map[k][j]);


	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (map[i][j] != INF)
				mmax[i] = max(mmax[i], map[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (map[i][j] == INF)
				res = min(res, mmax[i] + mmax[j] + dist(i, j));
	for (int i = 1; i <= n; i++)
		res = max(res, mmax[i]);
	printf("%lf\n", res);
	return 0;
}
