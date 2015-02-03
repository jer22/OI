#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	Node *fail;
	Node *next[26];
	int cnt;
	Node() {
		cnt = 0;
		fail = NULL;
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
	}
};

int T;
int n;
char s[1000005];
Node *root;
void insert(char *p) {
	int len = strlen(p);
	Node *pos = root;
	for (int i = 0; i < len; i++) {
		int idx = p[i] - 'a';
		if (pos -> next[idx] == NULL)
			pos -> next[idx] = new Node();
		pos = pos -> next[idx];
	}
	pos -> cnt++;
}

void build() {
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node * p = q.front();
		Node * temp = NULL;
		q.pop();
		for (int i = 0; i < 26; i++) {
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

int query() {
	int len = strlen(s);
	int ans = 0;
	Node *p = root;
	for (int i = 0; i < len; i++) {
		int idx = s[i] - 'a';
		while (p -> next[idx] == NULL && p != root)
			p = p -> fail;
		p = p -> next[idx];
		if (p == NULL) p = root;
		Node *temp = p;
		while (temp != root && temp -> cnt != -1) {
			ans += temp -> cnt;
			temp -> cnt = -1;
			temp = temp -> fail;
		}
	}
	return ans;
}

int main() {
	freopen("2222.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		root = new Node();
		scanf("%d", &n);
		char p[55];
		for (int i = 0; i < n; i++) {
			scanf("%s", p);
			insert(p);
		}
		build();
		scanf("%s", s);
		printf("%d\n", query());
	}
	return 0;
}
