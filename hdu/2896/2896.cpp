#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	Node *fail;
	Node *next[127];
	int sgn;
	Node() {
		sgn = 0;
		fail = NULL;
		for (int i = 0; i < 127; i++)
			next[i] = NULL;
	}
};

int n, m;
char s[10005];
Node *root;
void insert(char *p, int sgn) {
	int len = strlen(p);
	Node *pos = root;
	for (int i = 0; i < len; i++) {
		int idx = p[i];
		if (pos -> next[idx] == NULL)
			pos -> next[idx] = new Node();
		pos = pos -> next[idx];
	}
	pos -> sgn = sgn;
}

void build() {
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) {
		Node *p = q.front();
		Node *temp = NULL;
		q.pop();
		for (int i = 0; i < 127; i++) {
			if (p -> next[i] == NULL) continue;
			if (p == root) p -> next[i] -> fail = root;
			else {
				temp = p -> fail;
				while (temp != NULL) {
					if (temp -> next[i] != NULL) {
						p -> next[i] -> fail = temp -> next[i];
						break;
					}
					temp = temp -> fail;
				}
				if (temp == NULL) p -> next[i] -> fail = root;
			}
			q.push(p -> next[i]);
		}
	}
}

int ans[5];
bool vis[505];
int query() {
	memset(vis, 0, sizeof(vis));
	int cnt = 0;
	int len = strlen(s);
	Node *p = root;
	for (int i = 0; i < len; i++) {
		int idx = s[i];
		while (p -> next[idx] == NULL && p != root)
			p = p -> fail;
		p = p -> next[idx];
		if (p == NULL) p = root;
		Node *temp = p;
		while (temp != root) {
			if (temp -> sgn && !vis[temp -> sgn]) {
				ans[++cnt] = temp -> sgn;
				vis[temp -> sgn] = 1;
			}
			temp = temp -> fail;
		}
	}
	return cnt;
}

int main() {
	freopen("2896.in", "r", stdin);
	while (~scanf("%d", &n)) {
		root = new Node();
		char p[205];
		for (int i = 0; i < n; i++) {
			scanf("%s", p);
			insert(p, i + 1);
		}
		build();
		scanf("%d", &m);
		int tot = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%s", s);
			int cnt = query();
			if (!cnt) continue;
			tot++;
			printf("web %d:", i);
			sort(ans + 1, ans + cnt + 1);
			for (int i = 1; i <= cnt; i++) printf(" %d", ans[i]);
			printf("\n");
		}
		printf("total: %d\n", tot);
	}
	return 0;
}
