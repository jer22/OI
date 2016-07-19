#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch
#define this l, r, rt

using namespace std;

const int MAXN = 10005;

struct Seg{
	int h, l, r;
	int pos;
	int color;
	Seg() {}
	Seg(int a, int b, int c, int d, int e) : l(a), r(b), h(c), pos(d), color(e) {}
	bool operator < (const Seg &ss) const {
		if (h != ss.h) return h < ss.h;
		return pos > ss.pos;
	}
}hor[MAXN << 1];

int T, n;
int cols[MAXN];
int rects[MAXN][4];
set<int> p;
int ha[MAXN << 2];
map<int, int> m;
int cnt[MAXN << 4];
int sum[MAXN << 4];

int getnex(int ty, int i) {
	for (int j = i + 1; j < n << 1; j++) {
		if (hor[j].color & ty) return j;
	}
	return -1;
}

void pushup(int l, int r, int rt) {
	if (cnt[rt]) sum[rt] = ha[r + 1] - ha[l]; // covered over 1 time
	else if (l == r) sum[rt] = 0; // leaf
	else sum[rt] = sum[lch] + sum[rch];
}

void update(int L, int R, int pos, int l, int r, int rt) {
	int m = l + r >> 1;
	if (L <= l && r <= R) {
		cnt[rt] += pos;
		pushup(this);
		return;
	}
	if (L <= m) update(L, R, pos, lson);
	if (m < R) update(L, R, pos, rson);
	pushup(this);
}


long long ans[10];
int main() {
	freopen("4419.in", "r", stdin);
	scanf("%d", &T);
	int cas = 0;
	while (cas++ < T) {
		scanf("%d", &n);
		char s[3];
		p.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s %d %d %d %d", s, &rects[i][0], &rects[i][1], &rects[i][2], &rects[i][3]);
			p.insert(rects[i][0]);
			p.insert(rects[i][1]);
			p.insert(rects[i][2]);
			p.insert(rects[i][3]);
			if (s[0] == 'R') cols[i] = 1;
			else if (s[0] == 'G') cols[i] = 2;
			else cols[i] = 4;
		}
		int np = 0;
		m.clear();
		memset(ha, 0, sizeof(ha));
		for (set<int>::iterator it = p.begin(); it != p.end(); it++) {
			ha[++np] = *it;
			m[*it] = np;
		}
		for (int i = 0; i < n; i++) {
			hor[i << 1] = Seg(m[rects[i][0]], m[rects[i][2]], m[rects[i][1]], 1, cols[i]);
			hor[i << 1 | 1] = Seg(m[rects[i][0]], m[rects[i][2]], m[rects[i][3]], -1, cols[i]);
		}
		sort(hor, hor + (n << 1));
		// for (int i = 0; i < n << 1; i++) {
		// 	cout << hor[i].h << endl;
		// }
		memset(ans, 0, sizeof(ans));
		for (int ty = 1; ty <= 7; ty++) {
			memset(cnt, 0, sizeof(cnt));
			memset(sum, 0, sizeof(sum));	
			for (int i = 0; i < (n << 1); i++) {
				if (!(ty & hor[i].color)) continue;
				
				update(hor[i].l, hor[i].r - 1, hor[i].pos, 0, 40000, 1);
				int t = getnex(ty, i);
				// cout << t << endl;
				if (t == -1) break;
				ans[ty] += (long long)sum[1] * (ha[hor[t].h] - ha[hor[i].h]);
		
			}
		}
		long long a = ans[7] - ans[6];
		long long b = ans[7] - ans[5];
		long long c = ans[7] - ans[3];
		long long d = ans[7] - ans[4] - a - b;
		long long e = ans[7] - ans[2] - a - c;
		long long f = ans[7] - ans[1] - b - c;
		long long g = ans[7] - a - b - c - d - e - f;
		printf("Case %d:\n", cas);
		printf("%lld\n%lld\n%lld\n%lld\n%lld\n%lld\n%lld\n", a, b, c, d, e, f, g);
	}


	return 0;
}
