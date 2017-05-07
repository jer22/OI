#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 100005;

struct Point{
	int x, y, id;
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y > p.y;
	}
};

int n;
Point arr[MAXN];
int mx[MAXN * 80];
int ans[MAXN];

void pushup(int rt) {
	mx[rt] = max(mx[lch], mx[rch]);
}
int query(int l, int r, int rt, int L, int R) {
	if (L <= l && r <= R) {
		return mx[rt];
	}
	int mid = l + r >> 1;
	int ret = 0;
	if (L <= mid) ret = max(ret, query(lson, L, R));
	if (mid < R) ret = max(ret, query(rson, L, R));
	return ret;
}

void insert(int l, int r, int rt, int p, int v) {
	if (l == r) {
		if (v > mx[rt]) {
			mx[rt] = v;
		} else if (v == mx[rt]) {

		}
		return;
	}
	int mid = l + r >> 1;
	if (p <= mid) insert(lson, p, v);
	else insert(rson, p, v);
	pushup(rt);
}

vector<Point> num[MAXN];
int main() {
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i].x, &arr[i].y);
		arr[i].x += 1000002;
		arr[i].y += 1000002;
		arr[i].id = i;
	}
	sort(arr + 1, arr + n + 1);
	int mmx = 0;
	for (int i = 1; i <= n; i++) {
		ans[i] = query(1, 2000005, 1, 1, arr[i].y - 1) + 1;
		insert(1, 2000005, 1, arr[i].y, ans[i]);
		num[ans[i]].push_back(arr[i]);
		mmx = max(mmx, ans[i]);
	}
	vector<int> A, B;
	for (int i = 0; i < num[mmx].size(); i++)
		A.push_back(num[mmx][i].id);
	if (num[mmx].size() == 1) B.push_back(num[mmx][0].id);
	vector<Point> pre = num[mmx];
	vector<Point> now;
	for (int i = mmx - 1; i >= 1; i--) {
		int pb = 0, pa = 0;
		int siza = pre.size(), sizb = num[i].size();
		int cnt = 0;
		int p;
		now.clear();
		for (; pa < siza; pa++) {
			while (pb < sizb && num[i][pb].x < pre[pa].x) {
				if (num[i][pb].y < pre[pa].y) {
					p = num[i][pb].id;
					A.push_back(p);
					now.push_back(num[i][pb]);
					cnt++;
				}
				++pb;
			}
		}
		pre.clear();
		for (int i = 0; i < now.size(); i++)
			pre.push_back(now[i]);
		if (cnt == 1) B.push_back(p);
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	int siza = A.size(), sizb = B.size();
	printf("%d", siza);
	for (int i = 0; i < A.size(); i++)
		printf(" %d", A[i]);
	printf("\n%d", sizb);
	for (int i = 0; i < B.size(); i++)
		printf(" %d", B[i]);
	printf("\n");
	return 0;
}
