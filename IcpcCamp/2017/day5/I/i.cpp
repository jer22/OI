#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n, q;
long long mob[MAXN];
bool vis[MAXN];
vector<int> pri[MAXN], fac[MAXN], pos[MAXN];
int arr[MAXN];
void init() {
	for (int i = 2; i <= 100000; i++) {
		if (vis[i]) continue;
		for (int j = i; j <= 100000; j += i) {
			vis[j] = 1;
			pri[j].push_back(i);
		}
	}
	for (int i = 1; i <= 100000; i++) {
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= 100000; j += i)
			mob[j] += delta;

		for (int j = 1; j < 1 << (pri[i].size()); j++) {
			int t = 1;
			for (int k = 0; k < pri[i].size(); k++)
				if (j >> k & 1) t *= pri[i][k];
			fac[i].push_back(t);
		}
	}
}

int getcnt(int a, int b, int x) {
	int l = 0, r = pos[x].size() - 1;
	if (!pos[x].size()) return 0;
	while (l < r) {
		int mid = l + r >> 1;
		if (pos[x][mid] >= a) r = mid;
		else l = mid + 1;
	}
	if (pos[x][l] < a) return 0;
	a = l;
	l = 0, r = pos[x].size() - 1;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (pos[x][mid] <= b) l = mid;
		else r = mid - 1;
	}
	if (pos[x][l] > b) return 0;
	b = l;
	return max(0, b - a + 1);
}

int cal(int a, int b, int x) {
	int cnt = 0;
	for (int i = 0; i < fac[x].size(); i++)
		cnt += getcnt(a, b, fac[x][i]) * mob[fac[x][i]] * -1;
	return cnt;
}

int main() {
	freopen("i.in", "r", stdin);
	init();
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		for (int j = 0; j < fac[arr[i]].size(); j++)
			pos[fac[arr[i]][j]].push_back(i);
	}
	int a, b, x;
	while (q--) {
		scanf("%d %d %d", &a, &b, &x);
		if (x == 1) {
			printf("%d\n", b);
			continue;
		}
		int l = a, r = b;
		while (l < r) {
			int mid = (l + r >> 1) + 1;
			if (cal(mid, b, x) == b - mid + 1) r = mid - 1;
			else l = mid;
		}
		if (cal(l, b, x) == b - l + 1) printf("-1\n");
		else printf("%d\n", l);
	}

	return 0;
}
