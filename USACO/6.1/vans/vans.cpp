/*
ID:shijiey1
LANG:C++
PROG:vans
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int n = 4;

struct Num{
	short arr[500];
	int len;
	void init(int i) {
		memset(arr, 0, sizeof(arr));
		arr[0] = i;
		len = 1;
	}
	void print() {
		for (int i = len - 1; i >= 0; i--) {
			cout << arr[i];
		}
		cout << endl;
	}
};

void operator += (Num &a, Num b) {
	a.len = max(a.len, b.len);
	for (int i = 0; i < a.len; i++) {
		a.arr[i] += b.arr[i];
		a.arr[i + 1] += a.arr[i] / 10;
		a.arr[i] %= 10;
	}
	if (a.arr[a.len]) a.len++;
}

int N;
int stat[1110];
int brk[1110][8], stack[8], top = 0, tot = 0;
Num dp[8][1110];
int main() {
	freopen("vans.in", "r", stdin);
	freopen("vans.out", "w", stdout);
	cin >> N;
	int m = 1 << ((n + 1) << 1);
	for (int i = 0; i < m; i++) {
		top = 0;
		for (int j = 0; j <= n; j++) {
			int x = i >> (j << 1);
			if ((x & 3) == 1) stack[top++] = j;
			if ((x & 3) == 2)
				if (top--) {
					brk[tot][j] = stack[top];
					brk[tot][stack[top]] = j;
				} else break;
			if ((x & 3) == 3) {
				top = -1;
				break;
			}
		}
		if (!top) stat[tot++] = i;
	}
	Num ans;
	ans.init(0);
	memset(dp, 0, sizeof(dp));
	dp[n][0].init(1);
	for (int k = 1; k <= N; k++) {
		for (int i = 0; i < tot; i++) {
			if (stat[i] & 3) dp[0][stat[i]].init(0);
			else dp[0][stat[i]] = dp[n][stat[i] >> 2];
		}
		for (int i = 1; i <= n; i++) {
			int x = (i - 1) << 1;
			memset(dp[i], 0, sizeof(dp[i]));
			for (int j = 0; j < tot; j++) {
				int p = (stat[j] >> x) & 3;
				int q = (stat[j] >> (x + 2)) & 3;
				// ## -> ()
				// 9 = (21)4
				if (!p && !q) dp[i][stat[j] | (9 << x)] += dp[i - 1][stat[j]];
				else if (p && q) {
					if (p == q) {
						// ((...)) -> 
						// ##...()
						// 5 = (11)4 : ## = (( ^ 5
						// () = )) ^ 3
						if (p == 1) dp[i][stat[j] ^ (5 << x) ^ (3 << (brk[j][i] << 1))] += dp[i - 1][stat[j]];
						// ((...)) ->
						// ()...##
						// 10 = (22)4
						else dp[i][stat[j] ^ (10 << x) ^ (3 << (brk[j][i - 1] << 1))] += dp[i - 1][stat[j]];
					} else {
						if (p == 1) {
							if (k == N && i == n && stat[j] == (9 << x)) ans += dp[i - 1][stat[j]];
						} else dp[i][stat[j] ^ (6 << x)] += dp[i - 1][stat[j]]; // )( -> ##, 6 = (12)4
					}
				} else {
					dp[i][stat[j]] += dp[i - 1][stat[j]];
					// #( -> (#
					dp[i][stat[j] ^ (p << x) ^ (q << x + 2) | (p << x + 2) | (q << x)] += dp[i - 1][stat[j]];
				}
			}
		}
	}
	ans += ans;
	ans.print();
	return 0;
}
