/*
ID:shijiey1
LANG:C++
PROG:cowcycle
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int f1, f2, r1, r2;
int front[8];
int rear[12];
int ansf[8];
int ansr[12];
double minans = 0x3f3f3f3f;
double ratio[55], diff[55];

void solve() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			double t = (double)front[i] / rear[j];
			ratio[cnt++] = t;
		}
	}
	sort(ratio, ratio + cnt);
	double s1 = 0, s2 = 0;
	for (int i = 0; i < cnt - 1; i++) {
		diff[i] = ratio[i + 1] - ratio[i];
		s1 += diff[i];
		s2 += diff[i] * diff[i];
	}
	double variance = s2 - s1 * s1 / (cnt - 1);
	if (variance < minans) {
		minans = variance;
		memcpy(ansf, front, sizeof(ansf));
		memcpy(ansr, rear, sizeof(ansr));
	}
}

void dfs2(int i, int k) {
	if (i == m) {
		if (front[n - 1] * rear[m - 1] >= front[0] * rear[0] * 3)
			solve();
		return;
	}
	for (int j = k; j <= r2 - (m - i - 1); j++) {
		rear[i] = j;
		dfs2(i + 1, j + 1);
	}
}

void dfs1(int i, int k) {
	if (i == n) {
		dfs2(0, r1);
		return;
	}
	for (int j = k; j <= f2 - (n - i - 1); j++) {
		front[i] = j;
		dfs1(i + 1, j + 1);
	}
}

int main() {
	freopen("cowcycle.in", "r", stdin);
	freopen("cowcycle.out", "w", stdout);
	scanf("%d %d %d %d %d %d", &n, &m, &f1, &f2, &r1, &r2);
	dfs1(0, f1);
	for (int i = 0; i < n; i++)
		cout << ansf[i] << " \n"[i == n - 1];
	for (int i = 0; i < m; i++)
		cout << ansr[i] << " \n"[i == m - 1];
	return 0;
}
