#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int cnt;
	Node *fail;
	Node *next[256];
}*root, Trie[1005];

int n, m, p;
int hash[256];
int tot;
void insert(unsigned char *str) {
	Node *pos = root;
	for (int i = 0; str[i]; i++) {
		int idx = hash[str[i]];
		if (pos -> next[idx] == NULL)
			pos -> next[idx] = Trie + tot++;
		pos = pos -> next[idx];
	}
	pos -> cnt++;
}

void build() {
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) {
		Node *p = q.front();
		Node *temp = NULL;
		q.pop();
		for (int i = 0; i < 256; i++) {
			if (!hash[i]) continue;
			while (temp != NULL && temp -> next[i] == NULL)
				temp = temp -> fail;
			if (p -> next[i] != NULL) {
				if (temp == NULL) p -> next[i] -> fail = root;
				else {
					p -> next[i] -> fail = temp -> next[i];
					p -> next[i] -> cnt += temp -> next[i] -> cnt;
				}
				q.push(p -> next[i]);
			} else {
				if (temp == NULL) p -> next[i] = root;
				else p -> next[i] = temp -> next[i];
			}
		}
	}
}

int main() {
	freopen("1625.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &m, &p)) {
		tot = 1;
		root = Trie;
		unsigned char str[15];
		unsigned char dict[55];
		cin >> dict;
		memset(hash, 0, sizeof(hash));
		for (int i = 0; i < n; i++)
			hash[dict[i]] = i;
		for (int i = 0; i < p; i++) {
			cin >> str;
			insert(str);
		}
		build();
	}


	return 0;
}
