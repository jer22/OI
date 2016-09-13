#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int arr[305][305];
int dir[5][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};

struct Node{
	int x, y, step;
	Node() {}
	Node(int a, int b, int c) : x(a), y(b), step(c) {}

};

int vis[305][305];

bool check(int i, int j) {
	return i >= 0 && j >= 0;
}

int bfs() {
	if (!arr[0][0]) return -1;
	queue<Node> q;
	q.push(Node(0, 0, 0));
	vis[0][0] = 1;

	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0], ny = cur.y + dir[i][1];
			if (!check(nx, ny)) continue;
			if (nx > 300 || ny > 300) return cur.step + 1;
			if (arr[nx][ny] == INF) return cur.step + 1;
			if (cur.step + 1 < arr[nx][ny]) {
				if (!vis[nx][ny]) {
					vis[nx][ny] = 1;
					q.push(Node(nx, ny, cur.step + 1));
				}
			}
		}
	}
	return -1;
}

int main() {
	freopen("1611.in", "r", stdin);
	int a, b, c;
	scanf("%d", &n);
	memset(arr, 0x3f, sizeof(arr));
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		for (int k = 0; k < 5; k++) {
			int ni = a + dir[k][0], nj = b + dir[k][1];
			if (!check(ni, nj)) continue;
			arr[ni][nj] = min(arr[ni][nj], c);
		}
		
	}
	int ans = bfs();
	cout << ans << endl;

	return 0;
}
