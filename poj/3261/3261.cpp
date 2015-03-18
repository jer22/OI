#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

const int MAXN = 20005;
const int MAXM = 1000005;

int n, K;
int arr[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], tmp[MAXM];
struct Node{
	int id, c[2];
} Count[MAXN], Count_b[MAXN];

void getSA() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[arr[i]]++;
	for (int i = 1; i < MAXM; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rank[i] = tmp[arr[i] - 1];
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
			for (k ? k-- : 0, j = sa[rank[i] - 1]; arr[i + k] == arr[j + k]; k++)
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
		}
	}
}

bool calc(int x) {
	int ans = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		if (height[i] < x) {
			ans = max(ans, cnt);
			cnt = 0;
		} else {
			if (!cnt) cnt++;
			cnt++;
		}
	}
	ans = max(ans, cnt);
	return ans >= K;
}

int main() {
	freopen("3261.in", "r", stdin);
	while (~scanf("%d %d", &n, &K)) {
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		getSA();
		getHeight();
		int l = 0, r = n;
		while (l < r) {
			if (l + 1 == r) {
				if (calc(r)) l = r;
				else r = l;
			} else {
				int mid = l + r >> 1;
				if (calc(mid)) l = mid;
				else r = mid;
			}
		}
		cout << l << endl;
	}
	return 0;
}
