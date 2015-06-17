#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <complex>

#define pi acos(-1)
#define E complex<double>

using namespace std;

const int MAXN = 250005;

int n, m, L;
int arr[MAXN], brr[MAXN];
E a[MAXN << 2], b[MAXN << 2];
E aa[MAXN << 2], bb[MAXN << 2];
int r[MAXN << 2], c[MAXN << 2], cc[MAXN << 2];

int nex[MAXN];
void getnext() {
	int i = 0, j = -1;
	nex[0] = -1;
	while (i < m) {
		if (j == -1 || brr[i] == brr[j])
			nex[++i] = ++j;
		else j = nex[j];
	}
}

bool flag = false;
int idx, ans = 0x3f3f3f3f;
void kmp() {
	int i = 0, j = 0;
	while (i < n && j < m) {
		if (j == -1 || arr[i] == brr[j]) {
			i++;
			j++;
		} else j = nex[j];
		if (j == m) {
			flag = true;
			int pos = i - m;
			int val = m - c[i - 1] - cc[i - 1];
			if (val < ans) {
				ans = val;
				idx = pos + 1;
			}
			j = nex[j];
		}
	}
}

int toint(char str[]) {
	int ans = 0;
	for (int i = 0; i < 7; i++) {
		if (str[i] - '0') ans |= 1;
		ans <<= 1;
	}
	return ans;
}

void fft(E *a, int f) {
	for (int i = 0; i < n; i++)
		if (i < r[i]) swap(a[i], a[r[i]]);
	for (int i = 1; i < n; i <<= 1) {
		E wn(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < n; j += (i << 1)) {
			E w(1, 0);
			for (int k = 0; k < i; k++, w *= wn) {
				E x = a[j + k];
				E y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
	if (f == -1) for (int i = 0; i < n; i++) a[i] /= n;
}

void calFFT() {
	n--;
	m = n << 1;
	for (n = 1; n <= m; n <<= 1) L++;
	for (int i = 0; i < n; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << L - 1);
	fft(a, 1);
	fft(b, 1);
	for (int i = 0; i < n; i++) a[i] *= b[i];
	fft(a, -1);
	for (int i = 0; i <= m; i++) c[i] = (int)(a[i].real() + 0.1);


	fft(aa, 1);
	fft(bb, 1);
	for (int i = 0; i < n; i++) aa[i] *= bb[i];
	fft(aa, -1);
	for (int i = 0; i <= m; i++) cc[i] = (int)(aa[i].real() + 0.1);
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d %d", &n, &m);
	char str[10];
	int tn = n;
	int tm = m;
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		arr[i] = toint(str);
		int t = str[7] - '0';
		a[i] = t;
		aa[i] = t ^ 1;
	}
	for (int i = 0; i < m; i++) {
		scanf("%s", str);
		brr[i] = toint(str);
		int t = str[7] - '0';
		b[m - i - 1] = t;
		bb[m - i - 1] = t ^ 1;
	}
	calFFT();
	n = tn, m = tm;
	getnext();
	kmp();
	if (!flag) {
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	printf("%d %d", ans, idx);

	return 0;
}
