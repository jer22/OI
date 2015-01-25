#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Num{
	long long top, under;
	Num() {}
	Num(int a, int b) : top(a), under(b) {}
};

int T;
int n, m;
long long arr[100005];
long long brr[300005];
Num s[100005];
Num p[300005];
int next[300005];

bool equal(Num a, Num b) {
	long long x = a.top * b.under;
	long long y = a.under * b.top;
	return x == y;
}

void getNext(int lenp) {
	next[0] = -1;
	int i = 0, j = -1;
	while (i < lenp) {
		if (j == -1 || equal(p[i], p[j]))
			next[++i] = ++j;
		else j = next[j];
	}
}

long long kmp(int lens, int lenp) {
	int i = 0, j = 0;
	long long cnt = 0;
	while (i != lens && j != lenp) {
		if (j == -1 || equal(s[i], p[j])) {
			i++;
			j++;
		} else j = next[j];
		if (j == lenp) {
			cnt++;
			j = next[j];
		}
	}
	return cnt;
}

int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%lld", &arr[i]);
		for (int i = 0; i < n - 1; i++) {
			s[i] = Num(arr[i + 1], arr[i]);
		}
		int k;
		long long ans = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {
				scanf("%lld", &brr[j]);
			}
			for (int j = 0; j < k - 1; j++) {
				p[j] = Num(brr[j + 1], brr[j]);
			}
			if (k > n) continue;
			getNext(k - 1);
			if (k == 1) ans += (long long)n;
			else ans += kmp(n - 1, k - 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
