#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Node {
	string stat;
	int step;
	Node() {}
	Node(string a, int b) : stat(a), step(b) {}
}cur;

Node start;
string ed;
map<string, bool> vis;
queue<Node> q;

bool check(string stat) {
	for (int i = 0; i < 6; i++) {
		if (stat[i] != ed[i]) return false;
	}
	return true;
}

void push(string str) {
	if (!vis[str]) {
		vis[str] = 1;
		q.push(Node(str, cur.step + 1));
	}
}

int bfs() {
	q.push(start);
	vis[start.stat] = 1;
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		// cout << cur.stat << endl;
		if (check(cur.stat)) return cur.step;
		string nex = cur.stat;
		int pos = cur.stat[6] - '0';
		// swap0
		swap(nex[0], nex[pos]);
		push(nex);
		// swap1
		nex = cur.stat;
		swap(nex[5], nex[pos]);
		push(nex);
		// up
		nex = cur.stat;
		if (nex[pos] != '9' && (nex[pos] != ed[pos])) nex[pos]++;
		push(nex);
		// down
		nex = cur.stat;
		if (nex[pos] != '0' && (nex[pos] != ed[pos])) nex[pos]--;
		push(nex);
		// right
		nex = cur.stat;
		if (pos != 5) {
			if (pos != 0) {
				if (nex[pos] == ed[pos]) nex[6]++;
			} else nex[6]++;
		}
		push(nex);
		// left
		nex = cur.stat;
		if (pos != 0) {
			if (pos != 5) {
				if (nex[pos] == ed[pos]) nex[6]--;
			} else nex[6]--;
		}
		push(nex);
	}
	return -1;
}

int main(){
	cin >> start.stat >> ed;
	start.step = 0;
	start.stat += '0';
	int ans = bfs();
	cout << ans << endl;
	return 0;
}
