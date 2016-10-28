#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 100005;

int n, q;
pii arr[MAXN];
int brr[MAXN];
int blocksize = 0, nblocks = 0;
int cnt[355][MAXN];
int lef[355], rig[355], block[MAXN];
long long mx[355][355];
int num[MAXN];
int s[MAXN], top = 0;
void solve(int l, int r) {
	long long ans = 0;
	for (int i = l; i <= r; i++) {
		if (!num[brr[i]]) s[++top] = brr[i];
		num[brr[i]]++;
		ans = max(ans, (long long)num[brr[i]] * arr[brr[i]].first);
	}
	while (top)
		num[s[top--]] = 0;
	printf("%lld\n", ans);
}

int main() {
	freopen("4241.in", "r", stdin);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].first);
		arr[i].second = i;
	}
	sort(arr + 1, arr + n + 1);
	blocksize = sqrt(n);
	nblocks = (n - 1) / blocksize + 1;
	for (int i = 1; i <= n; i++) {
		if (arr[i].first == arr[i - 1].first)
			brr[arr[i].second] = brr[arr[i - 1].second];
		else brr[arr[i].second] = i;
		block[i] = (i - 1) / blocksize + 1;
		if (!lef[block[i]]) lef[block[i]] = i;
		rig[block[i]] = i; 
	}
	for (int i = 1; i <= n; i++)
		cnt[block[i]][brr[i]]++;
	for (int i = 2; i <= nblocks; i++)
		for (int j = 1; j <= n; j++)
			cnt[i][j] += cnt[i - 1][j];
	for (int i = 1; i <= nblocks; i++) {
		long long ans = 0;

		for (int j = lef[i]; j <= n; j++) {
			if (!num[brr[j]]) s[++top] = brr[j];
			num[brr[j]]++;
			ans = max(ans, (long long)num[brr[j]] * arr[brr[j]].first);
			if (j == rig[block[j]]) mx[i][block[j]] = ans;
		}
		while (top) num[s[top--]] = 0;
	}
	int l, r;
	memset(num, 0, sizeof(num));
	while (q--) {
		scanf("%d %d", &l, &r);
		if (block[l] == block[r]){
			solve(l, r);
			continue;
		}
		long long ans = mx[block[l] + 1][block[r] - 1];
		for (int i = l; i <= rig[block[l]]; i++) {
			if (!num[brr[i]]) {
				s[++top] = brr[i];
				num[brr[i]] = cnt[block[r] - 1][brr[i]] - cnt[block[l]][brr[i]];
			}
		}
		for (int i = lef[block[r]]; i <= r; i++) {
			if (!num[brr[i]]) {
				s[++top] = brr[i];
				num[brr[i]] = cnt[block[r] - 1][brr[i]] - cnt[block[l]][brr[i]];
			}
		}
		for (int i = l; i <= rig[block[l]]; i++)
			num[brr[i]]++;
		for (int i = lef[block[r]]; i <= r; i++)
			num[brr[i]]++;
		while (top) {
			ans = max(ans, (long long)num[s[top]] * arr[s[top]].first);
			num[s[top--]] = 0;
		}
		printf("%lld\n", ans);
	}

	return 0;
}
