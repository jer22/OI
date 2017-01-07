#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 405;
const int INF = 0x3f3f3f3f;

struct Node {
	int x, y, t;
	Node() {}
	Node(int a, int b, int c) : x(a), y(b), t(c) {}
};

int dir[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

int n, num[MAXN], in[MAXN][MAXN], vis[MAXN][MAXN][8];
vector<Node> vec, ves;
queue<Node> q, nq;
int main() {
	// freopen("d.in", "r", stdin);
	scanf("%d", &n);
	q.push(Node(200, 200, 0));
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);

		memset(vis, 0, sizeof vis);

		while (!q.empty()) {
			Node temp = q.front();
			q.pop();
			in[temp.x][temp.y] = 1;
			int nx = temp.x, ny = temp.y;
			for (int j = 1; j < num[i]; j++) {
				nx += dir[temp.t][0];
				ny += dir[temp.t][1];
				in[nx][ny] = 1;
			}

			int t = (temp.t + 1) % 8;
			if (vis[nx + dir[t][0]][ny + dir[t][1]][t] == 0) {
				nq.push(Node(nx + dir[t][0], ny + dir[t][1], t));
				vis[nx + dir[t][0]][ny + dir[t][1]][t] = 1;
			}
			t = (temp.t + 7) % 8;
			if (vis[nx + dir[t][0]][ny + dir[t][1]][t] == 0) {
				nq.push(Node(nx + dir[t][0], ny + dir[t][1], t));
				vis[nx + dir[t][0]][ny + dir[t][1]][t] = 1;
			}
		}
		while (!nq.empty()) {
			q.push(nq.front());
			nq.pop();
		}
	}
	int ans = 0;
	for (int i = 0; i < 400; i++)
		for (int j = 0; j < 400; j++)
			ans += in[i][j];
	cout << ans << endl;
	return 0;
}