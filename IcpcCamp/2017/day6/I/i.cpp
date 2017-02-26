#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
// #include <unordered_map>
#include <set>
#include <queue>
#include <vector>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch
#define p(i, j) (((i) - 1) * n + (j - 1))
#define pii pair<int, int>
#define fi first
#define se second
#define mp make_pair
#define plii pair<long long, pii >

using namespace std;

const int MAXN = 10005;
const long long INF = 1000000000000000000LL;

struct Node{
	int a, b, c, d;
	int id;
};

int n, m, q;
long long arr[15][MAXN];
// unordered_map<int, long long> dist[MAXN << 2][12];
long long dis[15][15][MAXN];
bool vis[15][MAXN];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
long long ans[100005];

void fuck(int x, int y, int l, int r) {
	for(int i=l;i<=r;i++)
		for(int j=1;j<=m;j++)
			dis[x][j][i]=INF;
	priority_queue<plii,vector<plii>,greater<plii> > q;
	q.push(plii(0,pii(x, y)));
	while(!q.empty()){
		plii now=q.top(); q.pop();
		pii u=now.second;
		if(dis[x][u.first][u.second]!=INF) continue;
		dis[x][u.first][u.second]=now.first;
		for(int d=0;d<4;d++){
			pii v(u.first+dir[d][0],u.second+dir[d][1]);
			if(v.first>=1&&v.first<=m&&v.second>=l&&v.second<=r)
				q.push(plii(now.first+arr[v.first][v.second],v));
		}
	}
}

Node v[100005];
void build(int l, int r, int rt, Node *be, Node *en) {
	if (en < be) return;
	int mid = l + r >> 1;
	for (int i = 1; i <= m; i++) {
		fuck(i, mid, l, r);
	}
	for (Node *q = be; q <= en; q++) {
		for (int i = 1; i <= m; i++)
			ans[q->id] = min(ans[q->id], dis[i][q->a][q->b] + dis[i][q->c][q->d] + arr[i][mid]);
	}
	if (l == r) return;
	Node *top = be;
	for (Node *q = be; q <= en; q++) {
		if (q -> d <= mid || q -> b > mid)
			*top++ = *q;
	}
	en = --top;
	Node *mi = be;
	for (; mi <= en && mi -> d <= mid; mi++);
	build(lson, be, mi - 1);
	build(rson, mi, en);
}
int a, b, c, d;

int main() {
	freopen("i.in", "r", stdin);
	scanf("%d %d %d", &m, &n, &q);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%lld", &arr[j][i]);
	// build(1, n, 1);
	for (int i = 1; i <= q; i++) {
		ans[i] = INF;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		if (b > d) {
			swap(a, c);
			swap(b, d);
		}
		v[i] = ((Node){a, b, c, d, i});

	}
	sort(v + 1, v + q + 1, [](Node a, Node b) {return a.d < b.d;});
	build(1, n, 1, v + 1, v + q);
	for (int i = 1; i <= q; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
