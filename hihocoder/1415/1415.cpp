#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;
const int MAXM = 130;

int n, lena, lenb;
char a[MAXN], b[MAXN], s[MAXN];
int sa[MAXN << 1], rk[MAXN << 1], height[MAXN << 1], tmp[MAXN << 1];
struct Node{
	int id, c[2];
	bool operator != (const Node &n) const{
		return c[0] != n.c[0] || c[1] != n.c[1];
	}
} Count[MAXN << 1], Count_b[MAXN << 1];

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
			Count[i].c[1] = (i + (1 << j)) >= n ? -1 : rk[i + (1 << j)];
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < MAXN * 2; j++) tmp[j] += tmp[j - 1];
			for (int j = n - 1; j >= 0; j--) Count_b[--tmp[Count[j].c[i] + 1]] = Count[j];
			for (int j = 0; j < n; j++) Count[j] = Count_b[j];
		}
		rk[Count[0].id] = 0;
		for (int i = 1; i < n; i++) {
			rk[Count[i].id] = rk[Count[i - 1].id];
			if (Count[i] != Count[i - 1]) rk[Count[i].id]++;
		}
		j++;
	}
	for (int i = 0; i < n; i++) sa[rk[i]] = i;
}

void getheight() {
	int k = 0, j;
	for (int i = 0; i < n; height[rk[i++]] = k) {
		if (!rk[k]) k = 0;
		else {
			for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++) {
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
			}
		}
	}
}

bool check(int x) {
	int mi = 0x3f3f3f3f, mx = -1;
	for (int i = 1; i < n; i++) {
		if (height[i] >= x) {
			mi = min(mi, sa[i]);
			mx = max(mx, sa[i]);
			mi = min(mi, sa[i - 1]);
			mx = max(mx, sa[i - 1]);
		} else {
			if (mi < lena && mx > lena + 1) return true;
			mi = 0x3f3f3f3f;
			mx = -1;
		}
	}
	return false;
}

int main() {
	// freopen("1415.in", "r", stdin);
	scanf("%s", a);
	scanf("%s", b);
	lena = strlen(a), lenb = strlen(b);
	strcpy(s, a);
	s[lena] = '#';
	strcpy(s + lena + 1, b);
	n = lena + lenb + 1;
	getsa();
	getheight();
	int l = 0, r = min(lena, lenb);
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);

	return 0;
}
