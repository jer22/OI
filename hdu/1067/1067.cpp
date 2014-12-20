#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int map[4][8];
	int step;
	Node() {
		step = 0;
		memset(map, 0, sizeof(map));
		map[0][0] = 11;
		map[1][0] = 21;
		map[2][0] = 31;
		map[3][0] = 41;
	}
};

int T;
Node start;
int goal;

int getHash(int arr[4][8]) {
	long long hash = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			hash <<= 1;
			hash += arr[i][j];
		}
	}
	return hash % 1000007;
}

Node find(Node a, int b) {
	a.step++;
	for (int i = 0; i < 4; i++)
		for (int j = 1; j < 8; j++)
			if (a.map[i][j] == b) a.map[i][j] = 0;
	return a;
}

bool vis[1000011];
int bfs() {
	memset(vis, false, sizeof(vis));
	int hash = getHash(start.map);
	vis[hash] = 1;
	queue<Node> q;
	q.push(start);
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		if (getHash(cur.map) == goal) return cur.step;
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j < 8; j++) {
				if (cur.map[i][j] || !(cur.map[i][j - 1] % 10) || cur.map[i][j - 1] % 10 == 7) continue;
				Node nex = find(cur, cur.map[i][j - 1] + 1);
				nex.map[i][j] = cur.map[i][j - 1] + 1;
				hash = getHash(nex.map);
				if (!vis[hash]) {
					vis[hash] = 1;
					q.push(nex);
				}
			}
		}
	}
	return -1;
}

int main() {
	scanf("%d", &T);
	int end[4][8] = {{11,12,13,14,15,16,17,0}, {21,22,23,24,25,26,27,0},
		{31,32,33,34,35,36,37,0}, {41,42,43,44,45,46,47,0}};
	goal = getHash(end);
	while (T--) {
		start = Node();
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j <= 7; j++) {
				scanf("%d", &start.map[i][j]);
				if (start.map[i][j] % 10 == 1) start.map[i][j] = 0;
			}
		}
		int ans = bfs();
		cout << ans << endl;
	}
	return 0;
}
