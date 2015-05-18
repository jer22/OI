#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 50005;

struct Node{
	int l, r, id;
	long long a, b;
};

int n, m;
int c[MAXN], pos[MAXN];
long long s[MAXN], ans;

long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}

bool cmp(Node a, Node b) {
	if (pos[a.l] != pos[b.l]) return a.l < b.l;
	return a.r < b.r;
}

bool cmp1(Node a, Node b) {
	return a.id < b.id;
}

Node arr[MAXN];

long long sqr(long long x) { return x * x; }
void update(int p, int add) {
	ans -= sqr(s[c[p]]);
	s[c[p]] += add;
	ans += sqr(s[c[p]]);
}

void solve() {
	for (int i = 0, l = 1, r = 0; i < m; i++) {
		for (; r < arr[i].r; r++)
			update(r + 1, 1);
		for (; r > arr[i].r; r--)
			update(r, -1);
		for (; l < arr[i].l; l++)
			update(l, -1);
		for (; l > arr[i].l; l--)
			update(l - 1, 1);
		if (arr[i].l == arr[i].r) {
			arr[i].a = 0;
			arr[i].b = 1;
			continue;
		}
		arr[i].a = ans - (arr[i].r - arr[i].l + 1);
		arr[i].b = (long long)(arr[i].r - arr[i].l + 1) * (arr[i].r - arr[i].l);
		long long k = gcd(arr[i].a, arr[i].b);
		arr[i].a /= k;
		arr[i].b /= k;
	}
}

int main() {
	freopen("2038.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	int block = int(sqrt(n));
	for (int i = 1; i <= n; i++)
		pos[i] = (i - 1) / block + 1;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &arr[i].l, &arr[i].r);
		arr[i].id = i;
	}
	sort(arr, arr + m, cmp);
	solve();
	sort(arr, arr + m, cmp1);
	for (int i = 0; i < m; i++)
		printf("%lld/%lld\n", arr[i].a, arr[i].b);
	return 0;
}
