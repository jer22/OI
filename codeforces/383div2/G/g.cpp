#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct RSADFLKJ{
	int l, r, x, y, id;
};

struct URIEOW{
	int l, r, id;
};

const int MAXN = 200005;
const int MAXM = 128;

int n;
int len1, len2;
char s[MAXN];
int sa[MAXN], rk[MAXN], height[MAXN], c[MAXN];
int ST[MAXN][25];
int delta[MAXN];
// struct Node{
// 	int id, c[2];
// } Count[MAXN], Count_b[MAXN];
int t[MAXN], t2[MAXN];
void getSA(int l, int m) {
	int *x=t,*y=t2;
	for (int i=0;i<l;i++)
		c[x[i]=s[i]]++;
	for (int i=1;i<m;i++) c[i]+=c[i-1];
	for (int i=l-1;i>=0;i--)
		sa[--c[x[i]]]=i;
	for (int k=1;k<l;k<<=1)
	{
		int p=0;
		for (int i=l-k;i<l;i++) y[p++]=i;
		for (int i=0;i<l;i++) if (sa[i]>=k) y[p++]=sa[i]-k;
		for (int i=0;i<m;i++) c[i]=0;
		for (int i=0;i<l;i++) c[x[i]]++;
		for (int i=1;i<m;i++) c[i]+=c[i-1];
		for (int i=l-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1;x[sa[0]]=0;
		for (int i=1;i<l;i++)
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if (p>=l) break;
		m=p;
	}
}

void getHeight(int l = n) {
	for (int i=1;i<=l;i++)
		rk[sa[i]]=i;
	for (int i=0,k=0,j;i<l;i++) 
	{
		if (k) k--;
		j=sa[rk[i]-1];
		while (s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}

void initST() {
	for (int i = 1; i <= n; i++)
		ST[i][0] = height[i];
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			ST[i][j] = min(ST[i][j - 1], ST[i + (1 << j - 1)][j - 1]);
		}
	}
}

int LCP(int a, int b) {
	int x = rk[a], y = rk[b];
	if (x > y) swap(x, y);
	x++;
	int k = delta[y - x + 1];
	return min(ST[x][k], ST[y - (1 << k) + 1][k]);
}

int id[MAXN];
int wxwxyyy(int a, int b, int l) {
	int t = LCP(a, b);
	if (t >= l) return -1;
	return s[a + t] < s[b + t];
}
bool cmp(int a, int b) {
	bool flag = 0;
	int t;
	if (a > b) swap(a, b), flag = 1;
	if (b - a < len2) {
		t = wxwxyyy(len1, a, b - a);
		if (~t) return t ^ flag;
		t = wxwxyyy(len1 + b - a, len1, len2 - b + a);
		if (~t) return t ^ flag;
		t = wxwxyyy(a, n - b + a, b - a);
		if (~t) return t ^ flag;
	} else if (b - a > len2) {
		t = wxwxyyy(len1, a, len2);
		if (~t) return t ^ flag;
		t = wxwxyyy(a, a + len2, b - a - len2);
		if (~t) return t ^ flag;
		t = wxwxyyy(b - len2, len1, len2);
		if (~t) return t ^ flag;
	} else {
		t = wxwxyyy(len1, a, len2);
		if (~t) return t ^ flag;
	}
	return !flag;
}


int wxy[MAXN >> 1];
int dyc[MAXN >> 1][22];
int fuck(int a, int b) {
	return ~a ? (wxy[a] < wxy[b] ? a : b) : b;
}
int good(int fff[MAXN >> 1][22], int a, int b) {
	int k = delta[b - a + 1];
	return fuck(fff[a][k], fff[b - (1 << k) + 1][k]);
}
int ans[MAXN >> 1];
vector<RSADFLKJ> bad[400];
vector<URIEOW> fuckyou[400];
int goodfuck[MAXN >> 1][22];

int main() {
	freopen("g.in", "r", stdin);
	scanf("%s", s);
	len1 = strlen(s);
	scanf("%s", s + len1);
	n = strlen(s);
	for (int i = 0; i < n; i++)
		s[i] -= 'a' - 1;
	len2 = n - len1;
	delta[1]= 0;
	for (int i = 2; i < 200001; i++) delta[i] = delta[i >> 1] + 1;
	getSA(n + 1, 27);
	getHeight();
	initST();
	for (int i = 0; i <= len1; i++)
		id[i] = i;
	sort(id, id + len1 + 1, cmp);
	for (int i = 0; i <= len1; i++) {
		wxy[id[i]] = i;
		dyc[i][0] = i;
	}
	for (int j = 1; j <= delta[len1] + 1; j++)
		for (int i = 0; i + (1 << j) - 1 <= len1; i++)
			dyc[i][j] = fuck(dyc[i][j - 1], dyc[i + (1 << j - 1)][j - 1]);
	int q;
	memset(ans, -1, sizeof(ans));
	scanf("%d", &q);
	int l, r, k, x, y;
	int dydyccc = 200;
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d %d %d", &l, &r, &k, &x, &y);
		if (k >= dydyccc) {
			// for (int j = 0; j <= len1; j += k) {
			// 	int ll = max(j + x, l);
			// 	int rr = min(r, j + y);
			// 	if (ll <= rr) ans[i] = fuck(ans[i], good(dyc, ll, rr));
			// }
			for (; ; )	{
				int a = max(x, l), b = min(y, r);
				if (a <= b) ans[i] = fuck(ans[i], good(dyc, a, b));
				x += k, y += k;
				if (x > len1) break;
			}
		} else bad[k].push_back((RSADFLKJ){l, r, x, y, i});
	}
	for (k = 1; k < dydyccc; k++) {
		if (bad[k].empty()) continue;
		for (int i = 0; i < k; i++) fuckyou[i].clear();
		for (auto qq : bad[k]) {
			for (int i = qq.x; i <= qq.y; i++) {
				int ll = qq.l / k * k + i, rr = qq.r / k * k + i;
				while (ll < qq.l) ll += k;
				while (ll - k >= qq.l) ll -= k;
				while (rr > qq.r) rr -= k;
				if (ll <= rr) fuckyou[i].push_back((URIEOW){ll / k, rr / k, qq.id});
			}
		}
		for (int i = 0; i < k; i++) {
			if (fuckyou[i].empty()) continue;
			for (int j = i, p = 0; j <= len1; j += k)
				goodfuck[p++][0] = j;
			for (int j = 1; j <= delta[len1] + 1; j++)
				for (int ii = 0; ii + (1 << j) - 1 <= len1; ii++)
					goodfuck[ii][j] = fuck(goodfuck[ii][j - 1], goodfuck[ii + (1 << j - 1)][j - 1]);
			for (auto qq : fuckyou[i]) {
				ans[qq.id] = fuck(ans[qq.id], good(goodfuck, qq.l, qq.r));
			}
		}
	}
	for (int i = 0; i < q; i++) {
		printf("%d ", ans[i]);
	}

	return 0;
}
