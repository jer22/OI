#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

const int MOD = 100000;

int n, m, k, tot, root;
int nex[105][4], fail[105], tag[105];

struct matrix {
	int n, m;
	long long a[105][105];
	inline void init(const int &tn, const int &tm) {
		n = tn;
		m = tm;
		for (int i = 0; i < tn; i++)
			for (int j = 0; j < tm; j++)
				a[i][j] = 0;
	}
}origin;

inline matrix operator * (matrix a, matrix b) {
	matrix c;
	c.init(a.n, b.m);
	int i, j, k;
	for (i = 0; i < a.n; i++) {
		for (k = 0; k < a.m; k++) {
			if (!a.a[i][k]) continue;
			for (j = 0; j < b.m; j++) {
				(c.a[i][j] += (a.a[i][k] * b.a[k][j]) % MOD) %= MOD;
			}
		}
	}
	return c;
}

inline matrix pow(matrix a, int x) {
	matrix res;
	res.init(a.n, a.m);
	for (int i = 0; i < a.n; i++) {
		res.a[i][i] = 1;
	}
	while (x) {
		if (x & 1) {
			res = res * a;
		}
		x >>= 1;
		a = a * a;
	}
	return res;
}


int getIdx(char c) {
	if (c == 'A') return 0;
	if (c == 'C') return 1;
	if (c == 'G') return 2;
	if (c == 'T') return 3;
}

void insert(char str[], int id) {
	int len = strlen(str);
	int pos = root;
	for (int i = 0; i < len; i++) {
		int t = getIdx(str[i]);
		if (!nex[pos][t])
			nex[pos][t] = tot++;
		pos = nex[pos][t];
	}
	tag[pos] = 1;
}

void build() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		tag[p] += tag[fail[p]];
		int t;
		for (int i = 0; i < 4; i++) {
			if (!(t = nex[p][i]))
				nex[p][i] = nex[fail[p]][i];
			else {
				fail[t] = p ? nex[fail[p]][i] : 0;
				q.push(t);
			}
		}
	}
}


int main() {
	freopen("g.in", "r", stdin);
	scanf("%d %d", &m, &n);
	char str[15];
	root = 0;
	tot = 1;
	for (int i = 0; i < m; i++) {
		scanf("%s", str);
		insert(str, i);
	}
	build();
	origin.init(tot, tot);
	for (int i = 0; i < tot; i++) {
		for (int j = 0; j < 4; j++) {
			if (tag[nex[i][j]]) continue;
			origin.a[i][nex[i][j]]++;

		}
	}
	origin = pow(origin, n);
	long long ans = 0;
	for (int i = 0; i < tot; i++)
		(ans += origin.a[0][i]) %= MOD;
	printf("%lld\n", ans);
	
	return 0;
}
