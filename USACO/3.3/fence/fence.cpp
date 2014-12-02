/*
ID:shijiey1
PROG:fence
LANG:C++
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
		/*while (edges[s][i] >= 2) {
			edges[s][i] -= 2;
			edges[i][s] -= 2;
			ans[n++] = i;
			ans[n++] = s;
		}*/
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
