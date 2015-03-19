#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

#define MAXN 40005
#define MAXM 128

using namespace std;

inline bool isLetter(char c) { return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'); }
inline char toChar(char c) { return (c >= 'a' && c <= 'z') ? c : c - 'A' + 'a'; }

int n = 0;
char str[MAXN];
char s[MAXN];
int hash[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], tmp[MAXN];
int ST[MAXN][20];
struct Node{
	int id, c[2];
} Count[MAXN], Count_b[MAXN];

void getSA() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[s[i]]++;
	for (int i = 1; i < MAXM; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rank[i] = tmp[s[i] - 1];
	int j = 0;
	while ((1 << j) < n) {
		for (int i = 0; i < n; i++) {
			Count[i].id = i;
			Count[i].c[0] = rank[i];
			Count[i].c[1] = ((i + (1 << j)) >= n) ? -1 : rank[i + (1 << j)];
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < MAXN; j++) tmp[j] += tmp[j - 1];
			for (int j = n - 1; j >= 0; j--) Count_b[--tmp[Count[j].c[i] + 1]] = Count[j];
			for (int j = 0; j < n; j++) Count[j] = Count_b[j];
		}
		rank[Count[0].id] = 0;
		for (int i = 1; i < n; i++) {
			rank[Count[i].id] = rank[Count[i - 1].id];
			if (Count[i].c[0] != Count[i - 1].c[0] || Count[i].c[1] != Count[i - 1].c[1])
				rank[Count[i].id]++;
		}
		j++;
	}
	for (int i = 0; i < n; i++) sa[rank[i]] = i;
}

void getHeight() {
	int k = 0, j;
	for (int i = 0; i < n; height[rank[i++]] = k) {
		if (!rank[i]) k = 0;
		else {
			for (k ? k-- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
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
	int x = rank[a], y = rank[b];
	if (x > y) swap(x, y);
	x++;
	int k = log(y - x + 1) / log(2);
	return min(ST[x][k], ST[y - (1 << k) + 1][k]);
}

int main() {
	freopen("calfflac.in", "r", stdin);
	int t = 0;
	char c;
	while (~scanf("%c", &c)) {
		str[t++] = c;
	}
	for (int i = 0; i < strlen(str); i++) {
		if (!isLetter(str[i])) continue;
		hash[n] = i;
		s[n++] = toChar(str[i]);
	}
	int len = n;
	s[n++] = '#';
	for (int i = len - 1; i >= 0; i--)
		s[n++] = s[i];
	s[n] = '\0';
	getSA();
	getHeight();
	RMQ();
	int ans = 0, idx;
	n = len;
	for (int i = 0; i < n; i++) {
		int t = LCP(i, n * 2 - i) * 2 - 1;
		if (t > ans) {
			ans = t;
			idx = i;
		}
		if (i > 0) {
			int t = LCP(i, n * 2 - i + 1) * 2;
			if (t > ans) {
				ans = t;
				idx = i;
			}
		}
	}
	int ss = hash[idx - ans / 2];
	int ee;
	cout << ans << endl;
	if (ans % 2)
		ee = hash[idx + ans / 2];
	else
		ee = hash[idx + ans / 2 - 1];
	for (int i = ss; i <= ee; i++)
		cout << str[i];
	cout << endl;

	return 0;
}
