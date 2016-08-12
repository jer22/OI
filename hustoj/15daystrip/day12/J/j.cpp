#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Node{
	Node *fail;
	Node *next[4];
	int cnt;
}Trie[10005], *root;;

int getIdx(char c) {
	if (c == 'A') return 0;
	if (c == 'C') return 1;
	if (c == 'G') return 2;
	if (c == 'T') return 3;
}

int n, tot;
char s[1005];
void insert(char *p) {
	int len = strlen(p);
	Node *pos = root;
	for (int i = 0; i < len; i++) {
		int idx = getIdx(p[i]);
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

int dp[1005][1005];
int main() {
	freopen("j.in", "r", stdin);
	int cas = 0;
	while (~scanf("%d", &n)) {
		if (!n) break;
		cas++;
		memset(Trie, 0, sizeof(Trie));
		root = Trie;
		tot = 1;
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			// cout << s << endl;
			insert(s);
		}
		// cout << tot << endl;
		build();
		scanf("%s", s);
		memset(dp, 0x3f, sizeof(dp));
		int len = strlen(s);
		dp[0][0] = 0;
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < tot; j++) {
				if (dp[i][j] == INF) continue;
				for (int k = 0; k < 4; k++) {
					int nex = Trie[j].next[k] - Trie;
					if (Trie[nex].cnt) continue;
					dp[i + 1][nex] = min(dp[i + 1][Trie[j].next[k] - Trie], dp[i][j] + (k != getIdx(s[i])));
				}
			}
		}
		int ans = INF;
		for (int i = 0; i < tot; i++)
			ans = min(ans, dp[len][i]);
		if (ans == INF) ans = -1;
		printf("Case %d: %d\n", cas, ans);
	}


	return 0;
}
