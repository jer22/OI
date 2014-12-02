#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define MAXN 210

using namespace std;

int n, m;
int a, b;
int step[MAXN][MAXN];
int done[MAXN][MAXN];
queue<int> qx;
queue<int> qy;

void bfs(int a, int b) {
	
	qx.push(a);
	qy.push(b);
	while (!qx.empty()) {
		int x = qx.front();
		int y = qy.front();
		if (x - 1 >= 1 && y - 2 >= 1 && !done[x - 1][y - 2]) {
			step[x - 1][y - 2] = step[x][y] + 1;
			qx.push(x - 1);
			qy.push(y - 2);
			done[x - 1][y - 2] = 1;
		}
		if (x - 1 >= 1 && y + 2 <= m && !done[x - 1][y + 2]) {
			step[x - 1][y + 2] = step[x][y] + 1;
			qx.push(x - 1);
			qy.push(y + 2);
			done[x - 1][y + 2] = 1;
		}
		if (x + 1 <= n && y - 2 >= 1 && !done[x + 1][y - 2]) {
			step[x + 1][y - 2] = step[x][y] + 1;
			qx.push(x + 1);
			qy.push(y - 2);
			done[x + 1][y - 2] = 1;
		}
		if (x + 1 <= n && y + 2 <= m && !done[x + 1][y + 2]) {
			step[x + 1][y + 2] = step[x][y] + 1;
			qx.push(x + 1);
			qy.push(y + 2);
			done[x + 1][y + 2] = 1;
		}

		if (x - 2 >= 1 && y - 1 >= 1 && !done[x - 2][y - 1]) {
			step[x - 2][y - 1] = step[x][y] + 1;
			qx.push(x - 2);
			qy.push(y - 1);
			done[x - 2][y - 1] = 1;
		}
		if (x - 2 >= 1 && y + 1 <= m && !done[x - 2][y + 1]) {
			step[x - 2][y + 1] = step[x][y] + 1;
			qx.push(x - 2);
			qy.push(y + 1);
			done[x - 2][y + 1] = 1;
		}
		if (x + 2 <= n && y - 1 >= 1 && !done[x + 2][y - 1]) {
			step[x + 2][y - 1] = step[x][y] + 1;
			qx.push(x + 2);
			qy.push(y - 1);
			done[x + 2][y - 1] = 1;
		}
		if (x + 2 <= n && y + 1 <= m && !done[x + 2][y + 1]) {
			step[x + 2][y + 1] = step[x][y] + 1;
			qx.push(x + 2);
			qy.push(y + 1);
			done[x + 2][y + 1] = 1;
		}
		qx.pop();
		qy.pop(); 
	}
}

int main() {
	freopen("1443.in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &a, &b);
	memset(step, -1, sizeof(step));
	memset(done, 0, sizeof(done));
	step[a][b] = 0;
	done[a][b] = 1;
	bfs(a, b);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%-5d", step[i][j]);
		}
		printf("\n");
	}

	return 0;
}
