#include <bits/stdc++.h>

using namespace std;

#define lowbit(x) ((x) & (-(x)))
#define mid (((l) + (r)) >> 1)
#define lch ls[rt]
#define rch rs[rt]
#define lson l, mid, lch
#define rson mid + 1, r, rch
#define rt(i) 1, cnt[arr[i]], root[arr[i]]

const int MAXN = 100005;
const long long MOD = 1000000007ll;

inline void cinsert(int pos, int val, long long *c) {
	for (int i = pos; i <= MAXN; i += lowbit(i))
		c[i] += val;
}
inline long long cgetsum(int pos, long long *c) {
	long long ans = 0;
	for (int i = pos; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

int n;
int arr[MAXN], h[MAXN], tot = 0;

void inithash() {
	for (int i = 1; i <= n; i++)
		h[i] = arr[i];
	sort(h + 1, h + n + 1);
	tot = unique(h + 1, h + n + 1) - h - 1;
}

int gethash(int x) {
	return lower_bound(h + 1, h + 1 + tot, x) - h;
}

int cnt[MAXN], pos[MAXN];
long long presmall[MAXN], sufsmall[MAXN];
map<int, int> oripos[MAXN];
int root[MAXN], nodenum = 0, ls[MAXN << 2], rs[MAXN << 2];
long long sumpre[MAXN << 2], sumsuf[MAXN << 2];
long long sumsumpre[MAXN << 2], sumsumsuf[MAXN << 2];
long long siz[MAXN << 2];
long long tagpre[MAXN << 2], tagsuf[MAXN << 2];
void pushup(int rt) {
	sumpre[rt] = (sumpre[lch] + sumpre[rch] + MOD) % MOD;
	sumsuf[rt] = (sumsuf[lch] + sumsuf[rch] + MOD) % MOD;
	sumsumpre[rt] = (sumsumpre[lch] + sumsumpre[rch] + MOD) % MOD;
	sumsumsuf[rt] = (sumsumsuf[lch] + sumsumsuf[rch] + MOD) % MOD;
	siz[rt] = siz[lch] + siz[rch];
}
void pushdown(int rt) {
	if (tagpre[rt]) {
		(sumsumpre[lch] += (tagpre[rt] * sumpre[lch] + MOD) % MOD) %= MOD;
		(sumsumpre[rch] += (tagpre[rt] * sumpre[rch] + MOD) % MOD) %= MOD;

		tagpre[lch] += tagpre[rt];
		tagpre[rch] += tagpre[rt];
		tagpre[rt] = 0;
	}
	if (tagsuf[rt]) {
		(sumsumsuf[lch] += (tagsuf[rt] * sumsuf[lch] + MOD) % MOD) %= MOD;
		(sumsumsuf[rch] += (tagsuf[rt] * sumsuf[rch] + MOD) % MOD) %= MOD;

		tagsuf[lch] += tagsuf[rt];
		tagsuf[rch] += tagsuf[rt];
		tagsuf[rt] = 0;
	}
}

void build(int l, int r, int &rt, int col) {
	if (!rt) rt = ++nodenum;
	if (l == r) {
		int p = oripos[col][l];
		sumpre[rt] = presmall[p] % MOD;
		sumsuf[rt] = sufsmall[p] % MOD;
		sumsumpre[rt] = presmall[p] * (cnt[col] - l) % MOD;
		sumsumsuf[rt] = sufsmall[p] * (l - 1) % MOD;
		siz[rt] = 1;
		return;
	}
	build(lson, col);
	build(rson, col);
	pushup(rt);
}

long long query(int l, int r, int rt, int L, int R, long long *c) {
	if (L > R) return 0;
	if (L <= l && r <= R) return c[rt];
	pushdown(rt);
	long long ans = 0;
	if (L <= mid) (ans += query(lson, L, R, c)) %= MOD;
	if (mid < R) (ans += query(rson, L, R, c)) %= MOD;
	return (ans + MOD) % MOD;
}

void update1(int l, int r, int rt, int p, int val, long long *c) {
	if (l == r) {
		(((c[rt] += val) += MOD) %= MOD);
		return;
	}
	pushdown(rt);
	if (p <= mid) update1(lson, p, val, c);
	else update1(rson, p, val, c);
	pushup(rt);
}
void update2(int l, int r, int rt, int L, int R, long long val, long long *c1, long long *c2, long long *tag) {
	if (L > R) return;
	if (L <= l && r <= R) {
		((c1[rt] += c2[rt] * val % MOD) += MOD) %= MOD;
		tag[rt] += val;
		return;
	}
	pushdown(rt);
	if (L <= mid) update2(lson, L, R, val, c1, c2, tag);
	if (mid < R) update2(rson, L, R, val, c1, c2, tag);
	pushup(rt);
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	inithash();
	static long long c[MAXN];
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= n; i++) {
		arr[i] = gethash(arr[i]);
		pos[i] = ++cnt[arr[i]];
		presmall[i] = cgetsum(arr[i], c);
		cinsert(arr[i], 1, c);
		oripos[arr[i]][pos[i]] = i;
	}
	memset(c, 0, sizeof(c));
	for (int i = n; i >= 1; i--) {
		sufsmall[i] = cgetsum(arr[i], c);
		cinsert(arr[i], 1, c);
	}
	for (int i = 1; i <= tot; i++)
		build(1, cnt[i], root[i], i);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += (query(rt(i), 1, pos[i] - 1, sumpre) * query(rt(i), pos[i] + 1, cnt[arr[i]], sumsuf)) % MOD;
	int m, op, x;
	scanf("%d", &m);
	while (m--) {
		scanf("%d %d", &op, &x);
		op = op * 2 - 3;
		ans += op * ((query(rt(x), 1, pos[x] - 1, sumpre) * query(rt(x), pos[x] + 1, cnt[arr[x]], sumsuf)) % MOD);
		while (ans < 0) ans += MOD;
		ans %= MOD;

		ans += op * ((((query(rt(x), 1, pos[x] - 2, sumsumpre) - (query(rt(x), pos[x], cnt[arr[x]], siz) * query(rt(x), 1, pos[x] - 2, sumpre)) % MOD) + MOD) % MOD) * sufsmall[x]) % MOD;
		while (ans < 0) ans += MOD;
		ans %= MOD;
		ans += op * ((((query(rt(x), pos[x] + 2, cnt[arr[x]], sumsumsuf) - (query(rt(x), 1, pos[x], siz) * query(rt(x), pos[x] + 2, cnt[arr[x]], sumsuf)) % MOD) + MOD) % MOD) * presmall[x]) % MOD;
		while (ans < 0) ans += MOD;
		ans %= MOD;
		update1(rt(x), pos[x], op * presmall[x], sumpre);
		update1(rt(x), pos[x], op * sufsmall[x], sumsuf);
		update1(rt(x), pos[x], (op * (query(rt(x), pos[x] + 1, cnt[arr[x]], siz) * presmall[x] % MOD) + MOD) % MOD, sumsumpre);
		update1(rt(x), pos[x], (op * (query(rt(x), 1, pos[x] - 1, siz) * sufsmall[x] % MOD) + MOD) % MOD, sumsumsuf);

		update1(rt(x), pos[x], op, siz);
		update2(rt(x), 1, pos[x] - 1, op, sumsumpre, sumpre, tagpre);
		update2(rt(x), pos[x] + 1, cnt[arr[x]], op, sumsumsuf, sumsuf, tagsuf);
		while (ans < 0) ans += MOD;
		ans %= MOD;
		cout << ans << endl;
	}
	return 0;
}
