/*
ID:shijiey1
LANG:C++
PROG:fence8
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int board[52];
int rail[1025];
int sum;
int railsum[1025];
int mid;

int H() {
	return sum - railsum[mid];
}

bool dfsid(int r, int b, int sum) {
	if (r < 0) return true;
	if (sum > H()) return false;
	for (int i = b; i < n; i++) {
		if (board[i] >= rail[r]) {
			board[i] -= rail[r];
			bool flag;
			int nexsum = sum + (board[i] < rail[0]) ? board[i] : 0;
			if (r > 0 && rail[r - 1] == rail[r])
				flag = dfsid(r - 1, i, nexsum);
			else flag = dfsid(r - 1, 0, nexsum);
			board[i] += rail[r];
			if (flag) return true;
		}
	}
	return false;
}

int solve() {
	int ans = 0;
	int l = 0, r = m - 1;
	while (l <= r) {
		mid = l + r >> 1;
		if (dfsid(mid, 0, 0)) {
			ans = mid + 1;
			l = mid + 1;
		} else r = mid - 1;
	}
	return ans;
}

int main() {
	freopen("fence8.in", "r", stdin);
	freopen("fence8.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &board[i]);
		sum += board[i];
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
		scanf("%d", &rail[i]);
	sort(board, board + n);
	sort(rail, rail + m);
	railsum[0] = rail[0];
	for (int i = 1; i < m; i++)
		railsum[i] = railsum[i - 1] + rail[i];
	int ans = solve();
	cout << ans << endl;
	return 0;
}
