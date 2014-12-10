/*
ID:shijiey1
PROG:fence
LANG:C++
*/

/*
欧拉路。
如果有节点的度数为奇数，则以它作为起点，否则以编号最小的点做起点（注意题目没说节点是从1开始标号的）
dfs然后倒序输出。
至于为什么倒序才能保证字典序其实我也不知道。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int E;
int s = INF;
int edges[505][505];
int degree[505];
int n = 0;
int ans[1050];
void dfs(int s) {
	for (int i = 1; i <= 500; i++) {
		if (edges[s][i]) {
			edges[s][i]--;
			edges[i][s]--;
			dfs(i);
		}
	}
	ans[n++] = s;
}

int main() {
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);
	scanf("%d", &E);
	int a, b;

	for (int i = 0; i < E; i++) {
		scanf("%d %d", &a, &b);
		edges[a][b]++;
		edges[b][a]++;
		degree[a]++;
		degree[b]++;
		s = min(s, min(a, b));
	}
	for (int i = s; i <= 500; i++) {
		if (degree[i] % 2) {
			s = i;
			break;
		}
	}
	// printf("%d\n", s);
	dfs(s);
	for (int i = n - 1; i >= 0; i--) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
