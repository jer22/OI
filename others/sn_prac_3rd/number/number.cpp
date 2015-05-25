#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[105][8];
bool vis[100000];

bool issub(int a, int b) {
	int temp[8];
	for (int i = 1; i <= 5; i++) {
		temp[i] = b % 10;
		b /= 10;
	}
	for (int i = 1; i <= 5 - arr[a][0] + 1; i++) {
		bool flag = false;
		for (int j = 0; j < arr[a][0]; j++) {
			if (temp[i + j] != arr[a][j + 1]) {
				flag = true;
				break;
			}
		}
		if (!flag) return true;
	}
	return false;
}

void init() {
	for (int i = 0; i <= 99999; i++) {
		for (int j = 1; j <= n; j++) {
			if (issub(j, i)) {
				vis[i] = 1;
				break;
			}
		}
	}
}

int length(int x) {
	int len = 0;
	while (x) {
		len++;
		x /= 10;
	}
	return len;
}

bool hehe(int num, int pos) {
	if (!vis[num]) return false;
	int len = length(num);

	if (pos - len == 0) {
		int t = num;
		for (int i = 1; i < len; i++)
			t /= 10;
		if (t != 1) {
			return false;
		} else return true;
	}

	if (len <= 2) return true;
	if (len == 3) {
		return pos != 5;
	}
	if (len == 4) {
		// cout << pos << endl;
		if (pos == 5 || pos == 6 || pos == 9) return false;
		return true;
	}

	return pos == 11;
}

long long dp[15][100005];
int main() {
	freopen("number.in", "r", stdin);
	scanf("%d\n", &n);
	int x;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		while (x) {
			arr[i][++arr[i][0]] = x % 10;
			x /= 10;
		}
	}
	init();
	dp[1][1] = 1;
	for (int i = 2; i <= 11; i++) {
		for (int j = 0; j <= 99999; j++) {
			if (hehe(j, i)) continue;
			for (int k = 0; k <= 9; k++) {
				int nex = j / 10 + k * 10000;
				dp[i][j] += dp[i - 1][nex];
			}
		}
	}
	long long ans = 0;
	for (int i = 0; i <= 99999; i++)
		ans += dp[11][i];
	cout << ans << endl;

	return 0;
}
