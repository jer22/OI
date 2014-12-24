#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node{
	int stat, step;
	Node() {}
	Node(int a, int b) : stat(a), step(b) {}
};

int T;
int n;
char des[22];
Node start;
bool vis[1 << 16];
int bfs() {
	queue<Node> q;
	memset(vis, 0, sizeof(vis));
	q.push(start);
	vis[start.stat] = 1;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		if (cur.stat == (1 << (n << 1)) - 1) return cur.step;
		for (int i = 0; i < (n << 1); i++) {
			if ((1 << i) & cur.stat) continue;
			int temp = 0;
			for (int j = i; j < (i / n + 1) * n; j++) {
				if ((1 << j) & cur.stat) break;
				if (des[j] == des[i]) temp |= 1 << j;
			}
			for (int j = i - 1; j >= (i / n) * n; j--) {
				if ((1 << j) & cur.stat) break;
				if (des[j] == des[i]) temp |= 1 << j;
			}
			for (int j = temp; j; j = temp & (j - 1)) {
				if (vis[cur.stat | j]) break;
				vis[cur.stat | j] = 1;
				q.push(Node(cur.stat | j, cur.step + 1));
			}
			if (i >= n) continue;
			if (cur.stat & (1 << (i + n))) continue;
			temp = 0;
			for (int j = i; j < n; j++) {
				if (((1 << j) & cur.stat) || ((1 << (j + n)) & cur.stat)) break;
				if (des[j] == des[i]) temp |= 1 << j;
				if (des[j + n] == des[i]) temp |= 1 << (j + n);
			}
			for (int j = i - 1; j >= 0; j--) {
				if (((1 << j) & cur.stat) || ((1 << (j + n)) & cur.stat)) break;
				if (des[j] == des[i]) temp |= 1 << j;
				if (des[j + n] == des[i]) temp |= 1 << (j + n);
			}
			for (int j = temp; j; j = temp & (j - 1)) {
				if (vis[j | cur.stat]) continue;
				vis[cur.stat | j] = 1;
				q.push(Node(cur.stat | j, cur.step + 1));
			}
		}
	}
}

int main() {
	freopen("4012.in", "r", stdin);
	int cas = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d\n", &n);
		scanf("%s%s", des, des + n);
		start = Node(0, 0);
		int ans = bfs();
		printf("Case #%d: %d\n", cas++, ans);
	}
	return 0;
}
