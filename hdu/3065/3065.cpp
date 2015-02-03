#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	Node *fail;
	Node *next[26];
	int sgn;
	Node() {
		sgn = 0;
		fail = NULL;
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
	}
}*root;

int n;
char p[1005][55];
char s[2000005];

void insert(int x) {
	int len = strlen(p[x]);
	Node *pos = root;
	for (int i = 0; i < len; i++) {
		int idx = p[x][i] - 'A';
		if (pos -> next[idx] == NULL)
			pos -> next[idx] = new Node();
		pos = pos -> next[idx];
	}
	pos -> sgn = x;
}

void build() {
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) {
		Node *pp = q.front();
		Node *temp = NULL;
		q.pop();
		for (int i = 0; i < 26; i++) {
			if (pp -> next[i] == NULL) continue;
			if (pp == root) pp -> next[i] -> fail = root;
			else {
				temp = pp -> fail;
				while (temp != NULL) {
					if (temp -> next[i] != NULL) {
						pp -> next[i] -> fail = temp -> next[i];
						break;
					}
					temp = temp -> fail;
				}
				if (temp == NULL) pp -> next[i] -> fail = root;
			}
			q.push(pp -> next[i]);
		}
	}
}

int ans[1005];
void query() {
	memset(ans, 0, sizeof(ans));
	int len = strlen(s);
	int cnt = 0;
	Node *pp = root;
	for (int i = 0; i < len; i++) {
		int idx = s[i] - 'A';
		if (idx < 0 || idx >= 26) {
			pp = root;
			continue;
		}
		while (pp -> next[idx] == NULL && pp != root)
			pp = pp -> fail;
		pp = pp -> next[idx];
		if (pp == NULL) pp = root;
		Node *temp = pp;
		while (temp != root) {
			if (temp -> sgn) {
				ans[temp -> sgn]++;
			}
			temp = temp -> fail;
		}
	}
}

int main() {
	freopen("3065.in", "r", stdin);
	while (~scanf("%d", &n)) {
		root = new Node();
		for (int i = 1; i <= n; i++) {
			scanf("%s", p[i]);
			insert(i);
		}
		build();
		scanf("%s", s);
		query();
		for (int i = 1; i <= n; i++)
			if (ans[i]) printf("%s: %d\n", p[i], ans[i]);
	}


	return 0;
}
