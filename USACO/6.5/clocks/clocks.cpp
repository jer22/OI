/*
ID:shijiey1
LANG:C++
PROG:clocks
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define HASH_SIZE 999991

using namespace std;

struct Node{
	int stat[9];
	char trans[50];
	int cnt[9];
	int step;
	Node() {
		step = 0;
	}
};


bool trans[9][9] =
	{{1, 1, 0, 1, 1, 0, 0, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 1, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 1, 0, 0},
	{0, 1, 0, 1, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 1, 1, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 1, 1, 0, 1, 1}};

Node s = Node();
int vis[HASH_SIZE];

long hs[] = {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536};
int getHash(Node a) {
	int ans=0;
	for(int i = 0; i < 9; i++)
		ans += a.stat[i] * hs[i];
	return ans;
}

bool end(Node a) {
	for (int i = 0; i < 9; i++)
		if (a.stat[i] != 4) return false;
	return true;
}

bool check(Node a) {
	int hash = getHash(a);
	if (vis[hash]) return false;
	for (int i = 0; i < 9; i++)
		if (a.cnt[i] > 3) return false;
	vis[hash] = true;
	return true;
}

Node bfs() {
	queue<Node> q;
	q.push(s);
	vis[getHash(s)] = 1;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		for (int i = 0; i < 9; i++) {
			Node nex = cur;
			nex.trans[nex.step++] = i + 1;
			nex.cnt[i]++;
			for (int j = 0; j < 9; j++) {
				if (trans[i][j]) {
					nex.stat[j]++;
					if (nex.stat[j] == 5) nex.stat[j] = 1;
				}
			}
			if (end(nex)) return nex;
			if (check(nex))	q.push(nex);
		}
	}
	return s;
}

int main() {
	freopen("clocks.in", "r", stdin);
	freopen("clocks.out", "w", stdout);
	int t;
	for (int i = 0; i < 9; i++) {
		cin >> t;
		s.stat[i] = t / 3;
		s.cnt[i] = 0;
	}
	Node ans = bfs();
	for (int i = 0; i < ans.step; i++) {
		if (i) printf(" ");
		printf("%d", ans.trans[i]);
	}
	printf("\n");
	return 0;
}