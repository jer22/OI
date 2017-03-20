#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n, q;
int arr[MAXN];
int maxsum[MAXN][20];
int minsum[MAXN][20];
long long c[MAXN];
int cha[MAXN];

void insert(int p, int x) {
	for (int i = p; i < MAXN; i += i & -i)
		c[i] += x;
}

long long getsum(int p) {
	long long ans = 0;
	for (int i = p; i; i -= i & -i)
		ans += c[i];
	return ans;
}

void initST() {
	for (int i = 1; i <= n; i++)
		maxsum[i][0] = minsum[i][0] = arr[i];
	for (int j = 1; j <= 18; j++) {
		for (int i = 1; i <= n; i++) {
			if (i + (1 << j) - 1 <= n) {
				maxsum[i][j] = max(maxsum[i][j - 1], maxsum[i + (1 << (j - 1))][j - 1]);
				minsum[i][j] = min(minsum[i][j - 1], minsum[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
}

int getmin(int a, int b) {
	int k = log(b - a + 1) / log(2);
	return min(minsum[a][k], minsum[b - (1 << k) + 1][k]);
}

int getmax(int a, int b) {
	int k = log(b - a + 1) / log(2);
	return max(maxsum[a][k], maxsum[b - (1 << k) + 1][k]);
}

vector<int> fuck[1000005];
int solve(int d, int x) {
	int l = 0, r = fuck[d].size() - 1;
	if (r < 0) return -1;
	while (l < r) {
		int mid = l + r >> 1;
		if (fuck[d][mid] >= x) r = mid;
		else l = mid + 1;
	}
	if (fuck[d][l] != x) return -1;
	return l;
}

int main() {
	freopen("f.in", "r", stdin);
	while (~scanf("%d %d", &n, &q)) {
		for (int i = 1; i <= n; i++)
			c[i] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			insert(i, arr[i]);
			cha[i] = abs(arr[i] - arr[i - 1]);
		}
		for (int i = 1; i <= 1000000; i++) {
			fuck[i].clear();
		}
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j * j <= cha[i]; j++) {
				if (!(cha[i] % j)) {
					if (j != 1) fuck[j].push_back(i);
					if (j != cha[i] / j) fuck[cha[i] / j].push_back(i);
				}
			}
		}
		initST();
		int l, r;
		while (q--) {
			scanf("%d %d", &l, &r);
			if (r - l <= 1) {
				printf("Yes\n");
				continue;
			}
			int mi = getmin(l, r);
			int mx = getmax(l, r);
			int num = r - l + 1;
			if ((mx - mi) % (num - 1)) {
				printf("No\n");
				continue;
			}
			int d = (mx - mi) / (num - 1);
			if (d == 1 || d == 0) {
				printf("Yes\n");
				continue;
			}
			long long sum = (long long)(mi + mx) * num / 2ll;
			if (getsum(r) - getsum(l - 1) != sum) {
				printf("No\n");
				continue;
			}
			int a = solve(d, l + 1);
			int b = solve(d, r);
			if (a == -1 || b == -1) {
				printf("No\n");
				continue;
			}
			if (b - a + 1 == r - l) {
				printf("Yes\n");
			} else printf("No\n");
		}
	}
	return 0;
}
