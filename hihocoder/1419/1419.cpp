#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;
const int MAXM = 130;

int n;
char s[MAXN];
int rk[MAXN], sa[MAXN], height[MAXN], tmp[MAXN];
int st[MAXN][25];
struct Node{
	int id, c[2];
	bool operator != (const Node &n) const {
		return c[0] != n.c[0] || c[1] != n.c[1];
	}
} Count[MAXN], Count_b[MAXN];

void getsa() {
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

void getheight() {
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

void getst() {
	for (int i = 0; i < n; i++)
		st[i][0] = height[i];
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 0; i + (1 << j) - 1 < n; i++)
			st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	}
}

int lcp(int a, int b) {
	int x = rk[a], y = rk[b];
	if (x > y) swap(x, y);
	x++;
	int k = log(y - x + 1) / log(2);
	return min(st[x][k], st[y - (1 << k) + 1][k]);
}

int main() {
	// freopen("1419.in", "r", stdin);
	scanf("%s", s);
	n = strlen(s);
	getsa();
	getheight();
	getst();
	// cout << lcp()
	int ans = 1;
	for (int len = 1; len <= n; len++) {
		for (int j = 0; j + len < n; j += len) {
			int ll = lcp(j, j + len);
			ans = max(ans, ll / len + 1);
			if (j - len + ll % len >= 0)
				ans = max(ans, lcp(j - len + ll % len, j + ll % len) / len + 1);
		}
	}
	printf("%d\n", ans);
	
	return 0;
}