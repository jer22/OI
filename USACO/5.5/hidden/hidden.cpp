/*
ID:shijiey1
PROG:hidden
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int r[200005];
int sa[200005];
int wa[200005], wb[200005], wv[200005], Ws[200005];

int cmp(int *rr, int a, int b, int l) {
	return rr[a] == rr[b] && rr[a + l] == rr[b + l];
}

void suffix(int n, int m) {
	int *x = wa;
	int *y = wb;
	int *t;
	int i, j, p;
	for (i = 0; i < m; i++) Ws[i] = 0;
	for (i = 0; i < n; i++) Ws[x[i] = r[i]]++;
	for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
	for (i = n - 1; i >= 0; i--) sa[--Ws[x[i]]] = i;
	for (j = 1, p = 1; p < n; j *= 2, m = p) {
		for (p = 0, i = n - j; i < n; i++) y[p++] = i;
		for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (i = 0; i < n; i++) wv[i] = x[y[i]];
		for (i = 0; i < m; i++) Ws[i] = 0;
		for (i = 0; i < n; i++) Ws[wv[i]]++;
		for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--Ws[wv[i]]] = y[i];
		for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++) {
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
		}
	}
}

int main() {
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
	int n;
	cin >> n;
	char c;
	for (int i = 0; i < n; i++) {
		c = getchar();
		if (c == '\n') c = getchar();
		r[i] = r[i + n] = c - 'a';
	}
	n *= 2;
	r[n] = 26;
	suffix(n + 1, 27);
	for (int i = 0; i < n; i++) {
		if (sa[i] < n / 2) {
			cout << sa[i] << endl;
			return 0;
		}
	}

	return 0;
}
