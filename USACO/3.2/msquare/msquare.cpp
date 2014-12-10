/*
ID:shijiey1
PROG:msquare
LANG:C++
*/

/*
标准的宽搜，应该没什么难度吧。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Node {
	int deep;
	string stat, trans;
	Node() {
		stat = "        ";
		trans = "";
	}
};

string start = "12345678";
string end = "";
queue<Node> q;
map<string, int> done;
int main() {
	freopen("msquare.in", "r", stdin);
	freopen("msquare.out", "w", stdout);
	int t;
	for (int i = 0; i < 8; i++) {
		scanf("%d", &t);
		end += t + '0';
	}
	Node node;
	node.stat = start;
	node.trans = "";
	node.deep = 0;
	q.push(node);
	done[start] = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		if (now.stat == end) {
			cout << now.deep << endl << now.trans << endl;
			break;
		}
		Node next = Node();
		next.deep = now.deep + 1;

		next.trans = now.trans + 'A';
		for (int i = 0; i < 4; i++) {
			next.stat[i] = now.stat[7 - i];
			next.stat[7 - i] = now.stat[i];
		}
		if (!done[next.stat]) {
			q.push(next);
			done[next.stat] = 1;
		}
		next.trans = now.trans + 'B';
		for (int i = 0; i < 4; i++) {
			next.stat[i] = now.stat[(i + 3) % 4];
			next.stat[i + 4] = now.stat[(i + 5) % 4 + 4];
		}
		if (!done[next.stat]) {
			q.push(next);
			done[next.stat] = 1;
		}
		next.trans = now.trans + 'C';
		next.stat[0] = now.stat[0];
		next.stat[3] = now.stat[3];
		next.stat[4] = now.stat[4];
		next.stat[7] = now.stat[7];
		next.stat[1] = now.stat[6];
		next.stat[2] = now.stat[1];
		next.stat[5] = now.stat[2];
		next.stat[6] = now.stat[5];
		if (!done[next.stat]) {
			q.push(next);
			done[next.stat] = 1;
		}
	}

	return 0;
}
