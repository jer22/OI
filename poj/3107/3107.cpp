#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct node{
	int v;
	node *next;
} *head[110000], tree[110000];

int ptr;
int n;
int res[110000];
int tot = 0;
int dp[110000];
int ans = 0x3f3f3f3f;

void addEdge(int x, int y) {
	tree[ptr].v = y;
	tree[ptr].next = head[x],head[x] = &tree[ptr++];
	tree[ptr].v = x;
	tree[ptr].next = head[y],head[y] = &tree[ptr++];
}

void dfs1(int x, int pre) {
	node *p = head[x];
	dp[x] = 1;
	while (p != NULL) {
		if (p -> v != pre) {
			dfs1(p -> v, x);
			dp[x] += dp[p -> v];
		}
		p = p -> next;
	}
}

void dfs2(int x, int pre) {
	node *p = head[x];
	int num = 0;
	while (p != NULL) {
		if (p -> v != pre) {
			dfs2(p -> v, x);
			num = max(num, dp[p -> v]);
		}
		p = p -> next;
	}
	num = max(num, n - dp[x]);
	if (num < ans) {tot = 0; ans = num;}
	if (num <= ans) res[tot++] = x;
}

int main() {
	freopen("3107.in", "r", stdin);
	int a, b;
	while (~scanf("%d", &n)) {
		ptr = 1;
		memset(head, 0, sizeof(head));
		tot = 0;
		ans = 0x3f3f3f3f;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			addEdge(a, b);
		}
		dfs1(1, 0);
		dfs2(1, 0);
		sort(res, res + tot);
		for (int i = 0; i < tot; i++) {
			if (i) printf(" ");
			printf("%d", res[i]);
		}
		printf("\n");
	}


	return 0;
}
