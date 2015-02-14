#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define MOD 100000

using namespace std;

struct Node{
	int cnt;
	Node *fail;
	Node *next[4];
}Trie[100005], *root;

struct Martrix{
	int n;
	int num[105][105];
	Martrix(int nn) {
		n = nn;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				num[i][j] = 0;
	}
};

int lens;
int tot = 1;
int getIdx(char c) {
	if (c == 'A') return 0;
	if (c == 'C') return 1;
	if (c == 'G') return 2;
	if (c == 'T') return 3;
}

void insert(char *str) {
	int len = strlen(str);
	Node *pos = root;
	for (int i = 0; i < len; i++) {
		int idx = getIdx(str[i]);
		if (pos -> next[idx] == NULL)
			pos -> next[idx] = Trie + tot++;
		pos = pos -> next[idx];
	}
	pos -> cnt++;
}

void build() {
	queue<Node*> q;
	int i;
	root->fail = NULL;
	q.push(root);
	while (!q.empty()) {
		Node *p = q.front();
		q.pop();
		Node *temp = NULL;
		for (i = 0; i < 4; i++) {
			temp = p->fail;
			while (temp != NULL && temp->next[i] == NULL)
				temp = temp->fail;
			if (p->next[i] != NULL) {
				if (temp == NULL)
					p->next[i]->fail = root;
				else {
					p->next[i]->fail = temp->next[i];
					p->next[i]->cnt += temp->next[i]->cnt;
				}
				q.push(p->next[i]);
			} else {
				if (temp == NULL)
					p->next[i] = root;
				else
					p->next[i] = temp->next[i];
			}
		}
	}
}

Martrix init(Martrix ori) {
	for (int i = 0; i < tot; i++) {
		for (int j = 0; j < 4; j++) {
			if (Trie[i].next[j] == NULL) continue;
			int temp = Trie[i].next[j] - Trie;
			if (!Trie[temp].cnt)
				ori.num[i][temp]++;
		}
	}
	return ori;
}

Martrix operator * (Martrix a, Martrix b) {
	Martrix ans = Martrix(a.n);
	for (int i = 0; i < ans.n; i++) {
		for (int k = 0; k < ans.n; k++) {
			if (!a.num[i][k]) continue;
			for (int j = 0; j < ans.n; j++) {
				long long temp = (long long)a.num[i][k] * b.num[k][j];
				temp %= MOD;
				ans.num[i][j] += temp;
				ans.num[i][j] %= MOD;
			}
		}
	}
	return ans;
}

Martrix power(Martrix a, int b) {
	Martrix ans = Martrix(a.n);
	for (int i = 0; i < ans.n; i++)
		ans.num[i][i] = 1;
	while (b) {
		if (b & 1)
			ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}

int main() {
	freopen("2778.in", "r", stdin);
	int pn;
	scanf("%d %d", &pn, &lens);
	char p[12];
	root = Trie;
	for (int i = 0; i < pn; i++) {
		scanf("%s", p);
		insert(p);
	}
	build();
	Martrix ori = Martrix(tot);
	ori = init(ori);
	ori = power(ori, lens);
	int ans = 0;
	for (int i = 0; i < tot; i++)
		ans = (ans + ori.num[0][i]) % MOD;
	printf("%d\n", ans);
	return 0;
}
