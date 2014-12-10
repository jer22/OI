/*
ID:shijiey1
PROG:maze1
LANG:C++
*/

/*
先找到两个出口，然后两次dfs找到每个出口到所有地方的步数。
对于每一个空格，走出迷宫的步数为它分别走到两个出口的步数的最小值，然后再统计其中的最大值。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
int arr[210][95];
int dist1[210][95];
int dist2[210][95];
int x1, y1;
int x2, y2;

int min(int a, int b) {
	if (!a) return b;
	if (!b) return a;
	return a < b ? a : b;
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void bfs1(int x, int y) {
	int done[210][95];
	memset(done, 0, sizeof(done));
	dist1[x][y] = 1;

	queue<pair<int, int> > q;
	done[x][y] = 1;
	q.push(pair<int, int>(x, y));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = p.first + dx[i];
			int ny = p.second + dy[i];
			if (nx > 1 && nx < (n << 1) + 1 && ny > 1 && ny < (m << 1) + 1 && !arr[nx][ny] && !done[nx][ny]) {
				q.push(pair<int, int>(nx, ny));
				done[nx][ny] = 1;
				dist1[nx][ny] = dist1[p.first][p.second] + 1;
			}
		}
	}

}

void bfs2(int x, int y) {
	int done[210][95];
	memset(done, 0, sizeof(done));
	dist2[x][y] = 1;

	queue<pair<int, int> > q;
	done[x][y] = 1;
	q.push(pair<int, int>(x, y));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = p.first + dx[i];
			int ny = p.second + dy[i];
			if (nx > 1 && nx < (n << 1) + 1 && ny > 1 && ny < (m << 1) + 1 && !arr[nx][ny] && !done[nx][ny]) {
				q.push(pair<int, int>(nx, ny));
				done[nx][ny] = 1;
				dist2[nx][ny] = dist2[p.first][p.second] + 1;
			}
		}
	}
	
}

int main() {
	freopen("maze1.in", "r", stdin);
	freopen("maze1.out", "w", stdout);
	scanf("%d %d\n", &m, &n);
	char c;
	for (int i = 1; i <= (n << 1) + 1; i++) {
		for (int j = 1; j <= (m << 1) + 1; j++) {
			scanf("%c", &c);
			if (c != ' ') arr[i][j] = 1;
			if (!arr[i][j] && (i == 1 || i == (n << 1) + 1 || j == 1 || j == (m << 1) + 1)) {
				if (!x1) {
					x1 = i;
					y1 = j;
				} else {
					x2 = i;
					y2 = j;
				}
			}
		}
		getchar();
	}
	bfs1(x1, y1);
	bfs2(x2, y2);
	int ans = 0;
	for (int i = 1; i <= (n << 1) + 1; i++) {
		for (int j = 1; j <= (m << 1) + 1; j++) {
			dist1[i][j] = min(dist1[i][j], dist2[i][j]);
			ans = max(ans, dist1[i][j]);
		}
		
	}
	printf("%d\n", ans >> 1);
	return 0;
}
