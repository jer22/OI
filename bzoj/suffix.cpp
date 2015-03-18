#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

const int MAXN = 2005;
const int MAXM = 128;

int n;
char str[MAXN], s[MAXN];
int sa[MAXN], rk[MAXN], height[MAXN], tmp[MAXN];
int ST[MAXN][25];
struct Node{
	int id, c[2];
} Count[MAXN], Count_b[MAXN];

void getSA() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[s[i]]++;
	for (int i = 1; i < MAXM; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rk[i] = tmp[s[i] - 1];
	int j = 0;
	while ((1 << j) < n) {
		for (int i = 0; i < n; i++) {
			Count[i].id = i;
			Count[i].c[0] = rk[i];
			Count[i].c[1] = ((i + (1 << j)) >= n) ? -1 : rk[i + (1 << j)];
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < MAXN; j++) tmp[j] += tmp[j - 1];
			for (int j = n - 1; j >= 0; j--) Count_b[--tmp[Count[j].c[i] + 1]] = Count[j];
			for (int j = 0; j < n; j++) Count[j] = Count_b[j];
		}
		rk[Count[0].id] = 0;
		for (int i = 1; i < n; i++) {
			rk[Count[i].id] = rk[Count[i - 1].id];
			if (Count[i].c[0] != Count[i - 1].c[0] || Count[i].c[1] != Count[i - 1].c[1])
				rk[Count[i].id]++;
		}
		j++;
	}
	for (int i = 0; i < n; i++) sa[rk[i]] = i;
}

void getHeight() {
	int k = 0, j;
	for (int i = 0; i < n; height[rk[i++]] = k) {
		if (!rk[i]) k = 0;
		else {
			for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++)
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
		}
	}
}

void RMQ() {
	for (int i = 0; i < n; i++)
		ST[i][0] = height[i];
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 0; i + (1 << j) - 1 < n; i++) {
			ST[i][j] = min(ST[i][j - 1], ST[i + (1 << j - 1)][j - 1]);
		}
	}
}

int LCP(int a, int b) {
	int x = rk[a], y = rk[b];
	if (x > y) swap(x, y);
	x++;
	int k = log(y - x + 1) / log(2);
	return min(ST[x][k], ST[y - (1 << k) + 1][k]);
}

int main() {
	freopen("1297.in", "r", stdin);
	while (~scanf("%s", str)) {
		n = strlen(str);
		int tot = 0;
		for (int i = 0; i < n; i++) {
			s[tot++] = str[i];
		}
		s[tot++] = '#';
		for (int i = n - 1; i >= 0; i--) {
			s[tot++] = str[i];
		}
		n = tot;
		getSA();
		getHeight();
		RMQ();
		n = tot - 1 >> 1;
		int ans = 0;
		int idx;
		for (int i = 0; i < n; i++) {
			int t = LCP(i, n * 2 - i) * 2 - 1;
			if (t > ans) {
				ans = t;
				idx = i;
			}
			if (i > 0) {
				t = LCP(i, n * 2 - i + 1) * 2;
				if (t > ans) {
					ans = t;
					idx = i;
				}
			}
		}
		if (ans % 2) {
			ans >>= 1;
			for (int i = idx - ans; i <= idx + ans; i++)
				cout << s[i];
		} else {
			ans >>= 1;
			for (int i = idx - ans; i < idx + ans; i++)
				cout << s[i];
		}
		cout << endl;
	}
	return 0;
}
