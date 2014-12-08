/*
ID:shijiey1
LANG:C++
PROG:twofive
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

long long f[6][6][6][6][6];
int arr[6][6];
long long dp(int i1, int i2, int i3, int i4, int i5) {
	if (f[i1][i2][i3][i4][i5]) return f[i1][i2][i3][i4][i5];
	long long ans = 0;
	if (i1 + 1 <= 5)
		ans += dp(i1 + 1, i2, i3, i4, i5);
	if (i2 + 1 <= i1)
		ans += dp(i1, i2 + 1, i3, i4, i5);
	if (i3 + 1 <= i2)
		ans += dp(i1, i2, i3 + 1, i4, i5);
	if (i4 + 1 <= i3)
		ans += dp(i1, i2, i3, i4 + 1, i5);
	if (i5 + 1 <= i4)
		ans += dp(i1, i2, i3, i4, i5 + 1);
	f[i1][i2][i3][i4][i5] = ans;
	return ans;
}

void solveN(int i1,int i2,int i3,int i4,int i5, long long lef) {
	cout << i1 << ' ' << i2 << ' '  << i3 << ' ' << i4 << ' ' << i5 << endl;
	cout << lef << endl;
	int now = i1 + i2 + i3 + i4 + i5 + 1;
	if (now == 26) return;
	if (i1 + 1 <= 5) {
		if (f[i1+1][i2][i3][i4][i5] >= lef) {
			arr[1][i1 + 1] = now;
			solveN(i1 + 1, i2, i3, i4, i5, lef);
			return;
		} else lef-=f[i1+1][i2][i3][i4][i5];
	}
	if (i2 + 1 <= i1) {
		if (f[i1][i2 + 1][i3][i4][i5] >= lef) {
			arr[2][i2 + 1] = now;
			solveN(i1, i2 + 1, i3, i4, i5, lef);
			return;
		} else lef -= f[i1][i2 + 1][i3][i4][i5];
	}
	if (i3 + 1 <= i2) {
		if (f[i1][i2][i3 + 1][i4][i5] >= lef) {
			arr[3][i3 + 1] = now;
			solveN(i1, i2, i3 + 1, i4, i5, lef);
			return;
		} else lef -= f[i1][i2][i3 + 1][i4][i5];
	}
	if (i4 + 1 <= i3) {
		if (f[i1][i2][i3][i4 + 1][i5] >= lef) {
			arr[4][i4 + 1] = now;
			solveN(i1, i2, i3, i4 + 1, i5, lef);
			return;
		} else lef -= f[i1][i2][i3][i4 + 1][i5];
	}
	if (i5 + 1 <= i4) {
		if (f[i1][i2][i3][i4][i5 + 1] >= lef) {
			arr[5][i5 + 1] = now;
			solveN(i1, i2, i3, i4, i5 + 1, lef);
			return;
		} else lef -= f[i1][i2][i3][i4][i5 + 1];
	}

}

int ans = 0;
void solveW(int i1, int i2, int i3, int i4, int i5) {
	int now = i1 + i2 + i3 + i4 + i5 + 1;
	if (now == 26) return;
	if (i1 + 1 <= 5) {
		if (arr[1][i1 + 1] == now) {
			solveW(i1 + 1, i2, i3, i4, i5);
			return;
		} else ans += f[i1 + 1][i2][i3][i4][i5];
	}
	if (i2 + 1 <= i1) {
		if (arr[2][i2 + 1] == now) {
			solveW(i1, i2 + 1, i3, i5, i5);
			return;
		} else ans += f[i1][i2 + 1][i3][i4][i5];
	}
	if (i3 + 1 <= i2) {
		if (arr[3][i3 + 1] == now) {
			solveW(i1, i2, i3 + 1, i4, i5);
			return;
		} else ans += f[i1][i2][i3 + 1][i4][i5];
	}
	if (i4 + 1 <= i3) {
		if (arr[4][i4 + 1] == now) {
			solveW(i1, i2, i3, i4 + 1, i5);
			return;
		} else ans += f[i1][i2][i3][i4 + 1][i5];
	}
	if (i5 + 1 <= i4) {
		if (arr[5][i5 + 1] == now) {
			solveW(i1, i2, i3, i4, i5 + 1);
			return;
		} else ans += f[i1][i2][i3][i4][i5 + 1];
	}
}

int main() {
	freopen("twofive.in", "r", stdin);
	freopen("twofive.out", "w", stdout);
	f[5][5][5][5][5] = 1;
	dp(0, 0, 0, 0, 0);
	// cout << f[5][5][5][3][3] << endl;
	char q;
	cin >> q;
	if (q == 'N') {
		long long t;
		cin >> t;
		solveN(0, 0, 0, 0, 0, t);
		for (int i = 1; i <= 5; i++) {
			for (int j = 1; j <= 5; j++) {
				cout << (char)(arr[i][j] + 'A' - 1);
			}
		}
		cout << endl;
		return 0;
	} else {
		char str[26];
		cin >> str;
		for (int i = 0; i < 25; i++) {
			arr[i / 5 + 1][i % 5 + 1] = str[i] - 'A' + 1;
		}
		solveW(0, 0, 0, 0, 0);
		cout << ans + 1 << endl;
	}
	

	return 0;
}
