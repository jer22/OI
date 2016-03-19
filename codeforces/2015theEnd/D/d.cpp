#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 5005;
const int MAXM = 10;

int n;
char str[5005];
int dp[5005], sum[5005];

int sa[MAXN], rk[MAXN], height[MAXN], tmp[MAXN];
int ST[MAXN][25];
struct Node{
	int id, c[2];
} Count[MAXN], Count_b[MAXN];

void getSA() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[str[i]]++;
	for (int i = 1; i < MAXM; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rk[i] = tmp[str[i] - 1];
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

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", str);
	dp[0] = 1;
	sum[0] = 1;
	getSA();
	for (int i = 1; i < n; i++) {
		dp[i] = 1;
		int idx = i / 2 - 1;
		for (int j = 0; j <= idx; j++) {
			dp[i] += dp[j];
			dp[i] %= MOD;
		}
		for (int j = idx + 1; j < i; j++) {
			int tmp = dp[j] - 1;
			int idx = j - (i - j) + 1;
			// if (i == 3) cout << j << ' ' << j - (i - j) + 1 << endl;
			if (rk[j + 1] > rk[idx]) {
				idx -= 2;
				if (idx < 0) continue;

			} else {
				idx--;
				if (idx < 0) continue;
			}
			tmp -= sum[idx];
			dp[i] += max(tmp, 0);
		}
	}

	return 0;
}
