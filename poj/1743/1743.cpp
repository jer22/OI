#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

const int MAXN =  20005;
const int MAXM = 205;

int n;
int arr[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], tmp[MAXN];
struct Node{
	int id, c[2];
}Count[MAXN], Count_b[MAXN];

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
			for (int k = 0; k < n; k++) tmp[Count[k].c[i] + 1]++;
			for (int k = 1; k < MAXN; k++) tmp[k] += tmp[k - 1];
			for (int k = n - 1; k >= 0; k--) Count_b[--tmp[Count[k].c[i] + 1]] = Count[k];
			for (int k = 0; k < n; k++) Count[k] = Count_b[k];
		}
		rank[Count[0].id] = 0;
		for (int i = 1; i < n; i++) {
			rank[Count[i].id] = rank[Count[i - 1].id];
			if (Count[i].c[0] != Count[i - 1].c[0] || Count[i].c[1] != Count[i - 1].c[1]) rank[Count[i].id]++;
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
			for (k ? k-- : 0, j = sa[rank[i] - 1]; arr[i + k] == arr[j + k]; k++) {
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
			}
		}
	}
}

bool calc(int x) {
	int l, r;
	for (int i = 0; i < n; i++) {
		if (height[i] < x) {
			l = r = sa[i];
			continue;
		}
		l = min(l, sa[i]);
		r = max(r, sa[i]);
		if (r - l > x) return true;
	}
	return false;
}

int main() {
	freopen("1743.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		for (int i = 0; i < n; i++)
			arr[i] = arr[i + 1] - arr[i] + 87;
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}
		getSA();
		getHeight();
		int l = 0, r = n;
		while (l < r) {
			int mid = (l + r >> 1) + 1;
			if (calc(mid)) l = mid;
			else r = mid - 1;
		}
		if (l > 3) cout << l + 1 << endl;
		else cout << 0 << endl;
	}
	

	return 0;
}
