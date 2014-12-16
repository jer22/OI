#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Node{
	int stat;
	int step;
	Node() {}
	Node(int a, int b) : stat(a), step(b) {}
};

int T;
int start, end;
queue<Node> q;
int vis[11111];

void push(Node nex) {
	if (!vis[nex.stat]) {
		vis[nex.stat] = 1;
		q.push(nex);
	}
}

int bfs() {
	memset(vis, 0, sizeof(vis));
	while (!q.empty()) q.pop();
	Node e = Node(start, 0);
	vis[start] = 1;
	q.push(e);
	while (!q.empty()) {
		e = q.front();
		q.pop();
		if (e.stat == end) return e.step;
		Node nex;
		int a = e.stat / 1000;
		int b = e.stat % 1000 / 100;
		int c = e.stat % 100 / 10;
		int d = e.stat % 10;
		if (a == 9) nex = Node(e.stat - 8000, e.step + 1);
		else nex = Node(e.stat + 1000, e.step + 1);
		push(nex);
		if (a == 1) nex = Node(e.stat + 8000, e.step + 1);
		else nex = Node(e.stat - 1000, e.step + 1);
		push(nex);
		if (b == 9) nex = Node(e.stat - 800, e.step + 1);
		else nex = Node(e.stat + 100, e.step + 1);
		push(nex);
		if (b == 1) nex = Node(e.stat + 800, e.step + 1);
		else nex = Node(e.stat - 100, e.step + 1);
		push(nex);
		if (c == 9) nex = Node(e.stat - 80, e.step + 1);
		else nex = Node(e.stat + 10, e.step + 1);
		push(nex);
		if (c == 1) nex = Node(e.stat + 80, e.step + 1);
		else nex = Node(e.stat - 10, e.step + 1);
		push(nex);
		if (d == 9) nex = Node(e.stat - 8, e.step + 1);
		else nex = Node(e.stat + 1, e.step + 1);
		push(nex);
		if (d == 1) nex = Node(e.stat + 8, e.step + 1);
		else nex = Node(e.stat - 1, e.step + 1);
		push(nex);
		nex = Node(b * 1000 + a * 100 + c * 10 + d, e.step + 1);
		push(nex);
		nex = Node(a * 1000 + c * 100 + b * 10 + d, e.step + 1);
		push(nex);
		nex = Node(a * 1000 + b * 100 + d * 10 + c, e.step + 1);
		push(nex);
	}
	return 0;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &start, &end);
		int ans = bfs();
		printf("%d\n", ans);
	}
	return 0;
}
