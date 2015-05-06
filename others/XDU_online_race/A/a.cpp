#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	int l, r, id;
	Node() {}
	Node(int a, int b, int c) : l(a), r(b), id(c) {}
	bool operator < (const Node &n) const {
		return l < n.l;
	}
};

struct Que{
	int x, pos, ans;
	Que() {}
	Que(int a, int b) : x(a), pos(b) {}
	bool operator < (const Que &n) const {
		return x < n.x;
	}
};

bool cmp(Que a, Que b) {
	return a.pos < b.pos;
}

int T, n, m;
Node arr[100005];
Que query[100005];
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d %d %d", &arr[i].l, &arr[i].r, &arr[i].id);
		sort(arr + 1, arr + n + 1);
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d", &query[i].x);
			query[i].pos = i;
		}
		sort(query, query + m);
		int pos = 1;
		for (int i = 0; i < m; i++) {
			while (query[i].x > arr[pos].r && pos < n) pos++;
			if (query[i].x < arr[pos].l) query[i].ans = -1;
			else if (query[i].x > arr[pos].r) query[i].ans = -1;
			else query[i].ans = arr[pos].id;
		}
		sort(query, query + m, cmp);
		for (int i = 0; i < m; i++)
			printf("%d\n", query[i].ans);
	}


	return 0;
}
