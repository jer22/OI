#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Node{
	int stat[6];
	int step;
	Node() {}
	Node(int a[6], int b) {
		for (int i = 0; i < 6; i++)
			stat[i] = a[i];
		step = b;
	}
};

int s[8], e[8];
bool vis[7][7][7][7][7][7];

bool finish(int *a) {
	for (int i = 0; i < 6; i++)
		if (a[i] != e[i]) return false;
	return true;
}
int nex[6]; 
void change(int stat[6], int dir) {
	for (int i = 0; i < 6; i++)
		nex[i] = stat[i];
	int t = nex[0];
	if (dir == 0) {
		nex[0] = nex[5];
		nex[5] = nex[1];
		nex[1] = nex[4];
		nex[4] = t;
	}
	if (dir == 1) {
		nex[0] = nex[3];
		nex[3] = nex[1];
		nex[1] = nex[2];
		nex[2] = t;
	}
	if (dir == 2) {
		nex[0] = nex[2];
		nex[2] = nex[1];
		nex[1] = nex[3];
		nex[3] = t;
	}
	if (dir == 3) {
		nex[0] = nex[4];
		nex[4] = nex[1];
		nex[1] = nex[5];
		nex[5] = t;
	}
}

int bfs() {
	queue<Node> q;
	vis[s[0]][s[1]][s[2]][s[3]][s[4]][s[5]] = 1;
	q.push(Node(s, 0));
	int cnt = 0;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		cnt++;
		if (cnt > 1000) return -1;
		for (int i = 0; i < 4; i++) {
			change(cur.stat, i);

			if (finish(nex)) return cur.step + 1;
			if (!vis[nex[0]][nex[1]][nex[2]][nex[3]][nex[4]][nex[5]]) {
				q.push(Node(nex, cur.step + 1));
			}
		}
	}
	return -1;
}

int main() {
	freopen("f.in", "r", stdin);
	while (~scanf("%d", &s[0])) {
		for (int i = 1; i < 6; i++)
			scanf("%d", &s[i]);
		for (int i = 0; i < 6; i++)
			scanf("%d", &e[i]);
		memset(vis, 0, sizeof(vis));
		if (finish(s)) {
			printf("0\n");
			continue;
		}
		int ans = bfs();
		printf("%d\n", ans);
	}



	return 0;
}
