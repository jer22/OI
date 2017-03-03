#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 20005;
const int MAXM = 105;

int n, K;
int s[MAXN];
int sa[MAXN], rk[MAXN], height[MAXN], tmp[MAXN];
struct Node{
	int id, c[2];
	bool operator != (const Node &n) const{
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
			Count[i].c[1] = i + (1 << j) >= n ? -1 : rk[i + (1 << j)];
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < MAXN; j++) tmp[j] += tmp[j - 1];
			for (int j = n - 1; ~j; j--) Count_b[--tmp[Count[j].c[i] + 1]] = Count[j];
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
		if (!rk[i]) k = 0;
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
	int cnt = 0;
	for (int i = 1; i < n; i++) {
		// cout << height[i] << endl;
		if (height[i] >= x) cnt++;
		else cnt = 0;
		if (cnt >= K - 1) return true;
	}
	return false;
}

int main() {
	// freopen("1403.in", "r", stdin);
	scanf("%d %d", &n, &K);
	for (int i = 0; i < n; i++)
		scanf("%d", &s[i]);
	getsa();
	getheight();
	int l = 0, r = n;
	// check(4);
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);

	return 0;
}
