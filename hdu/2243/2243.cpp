#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int cnt;
	int index;
	Node *fail;
	Node *next[26];
	Node(int i) {
		index = i;
		cnt = 0;
		fail = NULL;
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
	}
} *root;

struct Martrix{
	int n;
	unsigned long long num[66][66];
	Martrix() {memset(num, 0, sizeof(num));}
	Martrix(int nn) {
		n = nn;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				num[i][j] = 0;
	}
};

int lens, pn;
int tot = 1;

void insert(char *str) {
	int len = strlen(str);
	Node *pos = root;
	for (int i = 0; i < len; i++) {
		int idx = str[i] - 'a';
		if (pos -> next[idx] == NULL)
			pos -> next[idx] = new Node(tot++);
		pos = pos -> next[idx];
	}
	pos -> cnt++;
}

Martrix ori;
void build() {
	queue<Node*> q;
	int i;
	root->fail = NULL;
	q.push(root);
	while (!q.empty()) {
		Node *p = q.front();
		q.pop();
		if (p -> cnt) continue;
		Node *temp = NULL;
		for (i = 0; i < 26; i++) {
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
			if (p -> next[i] -> cnt == 0)
				ori.num[p -> index][p -> next[i] -> index]++;
		}
	}
}

Martrix operator * (Martrix a, Martrix b) {
	Martrix ans = Martrix(a.n);
	for (int i = 0; i < ans.n; i++) {
		for (int k = 0; k < ans.n; k++) {
			if (!a.num[i][k]) continue;
			for (int j = 0; j < ans.n; j++)
				ans.num[i][j] += a.num[i][k] * b.num[k][j];
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

Martrix base, e;
void init() {
	base = Martrix(2);
	base.num[0][0] = 26ull;
	base.num[0][1] = 1;
	base.num[1][1] = 1;
	base.num[1][0] = 0;
	e = Martrix(33);
	for (int i = 0; i < 66; i++)
		e.num[i][i] = 1;
}

unsigned long long getTotal(long long m) {
	Martrix ans = e, b = base;
	m++;
	while (m) {
		if (m & 1)
			ans = ans * b;
		b = b * b;
		m >>= 1;
	}
	return ans.num[0][1] - 1;
}

unsigned long long solve(Martrix origin, long long k) {
	int n = origin.n;
	Martrix ans = e;
	Martrix base = Martrix(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			base.num[i][j] = origin.num[i][j];
	for (int i = 0; i < n; i++)
		for (int j = n; j < n << 1; j++)
			base.num[i][j] = (i == j - n);
	for (int i = n; i < n << 1; i++)
		for (int j = n; j < n << 1; j++)
			base.num[i][j] = (i == j);
	ans.n = base.n = n << 1;
	k++;
	while (k) {
		if (k & 1)
			ans = ans * base;
		base = base * base;
		k >>= 1;
	}
	unsigned long long res = 0;
	for (int i = n; i < n << 1; i++)
		res += ans.num[0][i];
	return res - 1;
}

int main() {
	freopen("2243.in", "r", stdin);
	init();
	while (~scanf("%d %d", &pn, &lens)) {
		char p[12];
		root = new Node(0);
		tot = 1;
		for (int i = 0; i < pn; i++) {
			scanf("%s", p);
			insert(p);
		}
		ori = Martrix(tot);
		build();
		unsigned long long total = getTotal((long long)lens);
		unsigned long long res = solve(ori, (long long)lens);
		unsigned long long ans = total - res;
		if (ans < 0) ans += 10330176681277348905ull;
		printf("%llu\n", ans);
	}
	return 0;
}
