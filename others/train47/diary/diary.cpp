#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;

int n, k;
int dp[MAXN];
int len;
int arr[MAXN];

void insert(int x) {
	int l = 1, r = len + 1;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (x >= dp[mid]) l = mid;
		else r = mid - 1;
	}
	if (l == len + 1) len++;
	dp[l] = x;
}

int main() {
	freopen("diary.in", "r", stdin);
	scanf("%d %d", &n, &k);
	dp[0] = 0x3f3f3f3f;
	int x;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 0; i < n; i++) {
		insert(arr[i]);
	}
	for (int i = 0; i < n; i++)
		cout << dp[i] << endl;

	return 0;
}
