#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int num[511];
	int len;
	Node() {
		memset(num, 0, sizeof(num));
		len = 0;
	}
	void print() {
		for (int i = 0; i < len; i++) {
			if (num[i] < 10) printf("%d", num[i]);
			else printf("%c", num[i] - 10 + 'A');
		}
		printf("\n");
	}
};

int T;
int n, c, m;
int getMod(Node x) {
	int ans = 0;
	for (int i = 0; i < x.len; i++) {
		ans = (ans * c + x.num[i]) % n;
	}
	return ans;
}

int num[17];
int vis[5111];
bool bfs() {
	memset(vis, 0, sizeof(vis));
	queue<Node> q;
	Node e = Node();
	for (int i = 1; i < 16; i++) {
		if (!num[i]) continue;
		e.num[e.len++] = i;
		int mod = getMod(e);
		if (!mod) {
			e.print();
			return true;
		} else if (!vis[mod]) {
			vis[mod] = 1;
			q.push(e);
		}
		e.len--;
	}
	while (!q.empty()) {
		e = q.front();
		q.pop();
		for (int i = 0; i < 16; i++) {
			if (!num[i]) continue;
			e.num[e.len++] = i;
			int mod = getMod(e);
			if (!mod) {
				e.print();
				return true;
			}
			else if (!vis[mod] && e.len < 499) {
				vis[mod] = 1;
				q.push(e);
			}
			e.len--;
		}
	}
	return false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(num, 0, sizeof(num));
		scanf("%d %d %d", &n, &c, &m);
		char str[2];
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			if (str[0] >= '0' && str[0] <= '9') num[str[0] - '0'] = 1;
			else num[str[0] - 'A' + 10] = 1;
		}
		if (!n) {
			if (num[0]) printf("0\n");
			else printf("give me the bomb please\n");
		} else {
			if (!bfs()) printf("give me the bomb please\n");
		}
	}

	return 0;
}
