#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

#define MAXN 50010

using namespace std;

struct Node {
    int val;
    int pos;    // pos:第几个读入的数字
    bool operator < (const Node &n) const {
        if (val != n.val) return val < n.val;
        else return pos < n.pos;
    }
};

int n;
Node a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int c1[MAXN], c2[MAXN], c3[MAXN], c4[MAXN];
int r1[MAXN], r2[MAXN], r3[MAXN], r4[MAXN];    // reflect[i]:第i个读入的数字的下标

int lowBit(int i) {
    return i & (-i);
}

void update(int x, int *y) {
    while (x <= n) {
        y[x]++;
        x += lowBit(x);
    }
}

int getSum(int x, int *y) {
    int ans = 0;
    while (x > 0) {
        ans += y[x];
        x -=lowBit(x);
    }
    return ans;
}

long long ni[MAXN], sh[MAXN];
long long nid[MAXN], shd[MAXN];
int main() {
	freopen("1012.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
	        scanf("%d", &a[i].val);
	        a[i].pos = b[i].pos = i;
	        b[i].val = -a[i].val;

	        c[n - i + 1].val = a[i].val;
	        d[n - i + 1].val = -a[i].val;
	        c[i].pos = d[i].pos = i;
	    }
	    sort(a + 1, a + n + 1);
	    sort(b + 1, b + n + 1);
	    sort(c + 1, c + n + 1);
	    sort(d + 1, d + n + 1);
	    for (int i = 1; i <= n; i++) {
	        r1[a[i].pos] = i;
	        r2[b[i].pos] = i;
	        r3[c[i].pos] = i;
	        r4[d[i].pos] = i;
	    }
	    memset(c1, 0, sizeof(c1));
	    memset(c2, 0, sizeof(c2));
	    memset(c3, 0, sizeof(c3));
	    memset(c4, 0, sizeof(c4));
	    for (int i = 1; i <= n; i++) {
	        update(r1[i], c1);
	        update(r2[i], c2);
	        update(r3[i], c3);
	        update(r4[i], c4);
	        ni[i] = ni[i - 1] + i - getSum(r1[i], c1);
	        sh[i] = sh[i - 1] + i - getSum(r2[i], c2);
	        nid[i] = nid[i - 1] + i - getSum(r3[i], c3);
	        shd[i] = shd[i - 1] + i - getSum(r4[i], c4);
	    }
	    long long ans = ni[n] * sh[n];

	    for (int i = 1; i <= n; i++) {
	    	// cout << ni[i] << ' ' << sh[i] << endl;
	    }

	    // cout << nid[n - 1] << endl;
	    for (int i = 1; i <= n; i++) {
	    	ans -= (sh[i] - sh[i - 1]) * (ni[i] - ni[i - 1]);
	    	ans -= (sh[i] - sh[i - 1]) * (shd[n - i + 1] - shd[n - i]);
	    	ans -= (ni[i] - ni[i - 1]) * (nid[n - i + 1] - nid[n - i]);
	    	ans -= (shd[n - i + 1] - shd[n - i]) * (nid[n - i + 1] - nid[n - i]);
	    	// cout << shd[n - i - 1];
	    }
	    cout << ans << endl;

	}
   
    return 0;
}