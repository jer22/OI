#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>

using namespace std;

struct Node{
	string pos, seq;
	int stat;
	Node() {}
	Node(string a, string b, int c) : pos(a), seq(b), stat(c) {}
	bool operator < (const Node &n) const {
		if (pos != n.pos) return pos < n.pos;
		return seq < n.seq;
	}
};

int n, m;
char id[15] = {'0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
string st = "", ed = "", nexp;
int ans = 0;
map<Node, bool> vis;
void spfa() {
	queue<Node> q;
	q.push(Node(st, "", 0));
	vis[Node(st, "", 0)] = 1;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		for (int i = 0; i < n; i++) {
			if ((cur.stat >> i) & 1) continue;
			int len = 1 << i;
			int nexs = cur.stat | len;
			string nexq = cur.seq + id[i + 1];

			for (int j = 0; j < m; j += len) {
				for (int k = j + len; k < m; k += len) {
					nexp = cur.pos;
					for (int l = 0; l < len; l++)
						swap(nexp[j + l], nexp[k + l]);
					if (nexp == ed) {
						// cout << nexq << endl;
						ans++;
					}
					else {
						if (!vis[Node(nexp, nexq, nexs)]) {
							vis[Node(nexp, nexq, nexs)] = 1;
							q.push(Node(nexp, nexq, nexs));
						}
					}
					
				}
			}
		}
		vis[cur] = 0;
	}
}

int main() {
	freopen("1945.in", "r", stdin);
	scanf("%d", &n);
	m = 1 << n;
	int t;
	for (int i = 0; i < m; i++) {
		scanf("%d", &t);
		st += id[t];
		ed += id[i + 1];
	}
	if (st == ed) {
		cout << 1 << endl;
		return 0;
	}
	spfa();
	cout << ans << endl;
	return 0;
}
