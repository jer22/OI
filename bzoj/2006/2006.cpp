#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

const int MAXN = 500005;

int n, k, minlen, maxlen;
long long arr[MAXN];
long long sum[MAXN];

int ST[MAXN][20];
int IDX[MAXN][20];
void initST() {
	for (int i = 1; i <= n; i++) {
		ST[i][0] = sum[i];
		IDX[i][0] = i;
	}
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			if (i + (1 << j) - 1 <= n) {
				if (ST[i][j - 1] > ST[i + (1 << j - 1)][j - 1]) {
					ST[i][j] = ST[i][j - 1];
					IDX[i][j] = IDX[i][j - 1];
				} else {
					ST[i][j] = ST[i + (1 << j - 1)][j - 1];
					IDX[i][j] = IDX[i + (1 << j - 1)][j - 1];
				}
			}
}
int query(int a, int b) {
	int k = log(b - a + 1) / log(2);
	return max(ST[a][k], ST[b - (1 << k) + 1][k]);
}
int query_idx(int a, int b) {
	int k = log(b - a + 1) / log(2);
	if (ST[a][k] > ST[b - (1 << k) + 1][k]) return IDX[a][k];
	else return IDX[b - (1 << k) + 1][k];
}

struct Node{
	int i, idx, l, r, v;
	Node() {}
	Node(int a, int b, int c, int d, int e)
		: i(a), idx(b), l(c), r(d), v(e) {}
	bool operator < (const Node &n) const {
		return v < n.v;
	}
};

priority_queue<Node> q;

int main() {
	scanf("%d %d %d %d", &n, &k, &minlen, &maxlen);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
	}
	initST();
	for (int i = 1; i + minlen - 1 <= n; i++) {
		int l = i + minlen - 1;
		int r = min(n, i + maxlen - 1);
		int v = query(l, r);
		int idx = query_idx(l, r);
		q.push(Node(i, idx, l, r, v - sum[i - 1]));
	}
	long long ans = 0;
	while (k--) {
		Node cur = q.top();
		q.pop();
		ans += cur.v;
		if (cur.idx > cur.l) {
			int l = cur.l;
			int r = cur.idx - 1;
			int v = query(l, r);
			int idx = query_idx(l, r);
			q.push(Node(cur.i, idx, l, r, v - sum[cur.i - 1]));
		}
		if (cur.idx < cur.r) {
			int l = cur.idx + 1;
			int r = cur.r;
			int v = query(l, r);
			int idx = query_idx(l, r);
			q.push(Node(cur.i, idx, l, r, v - sum[cur.i - 1]));
		}
	}
	printf("%lld\n", ans);
	return 0;
}
