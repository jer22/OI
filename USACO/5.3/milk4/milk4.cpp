/*
TASK:milk4
ID:shijiey1
LANG:C++
*/

/*
用dfsid枚举每一种取法，然后用完全背包判断是否符合题意。
不会超时。
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

int m, n;
int arr[105];
set<int> pail;
int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int t = 0;
int choose[105];
int dp[20005];
int cnt = 0;
bool ok(int cnt) {
	dp[0] = cnt;
	for (int i = 1; i <= t; i++) {
		for (int j = arr[choose[i - 1]]; j <= m; j++) {
			if (dp[j - arr[choose[i - 1]]] == cnt)
				dp[j] = cnt;
		}
	}
	return dp[m] == cnt;
}

void print() {
	cout << t;
	for (int i = 0; i < t; i++) {
		cout << ' ' << arr[choose[i]];
	}
	cout << endl;
}

bool flag = false;
void dfs(int depth, int i) {
	if (flag) return;
	if (!depth) {
		cnt++;
		if (ok(cnt)) {
			print();
			flag = true;
		}
		return;
	}
	if (i > n) return;
	for (int j = i; j <= n; j++) 
	if (t != 0 && (arr[j] % arr[choose[t - 1]]) || !t) {
		choose[t++] = j;
		dfs(depth - 1, j + 1);
		choose[--t] = 0;
	}
}

int main() {
	freopen("milk4.in", "r", stdin);
	freopen("milk4.out", "w", stdout);
	scanf("%d %d", &m, &n);
	int t;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t);
		pail.insert(t);
	}
	n = 0;
	for (set<int>::iterator it = pail.begin(); it != pail.end(); it++) {
		arr[++n] = *it;
	}
	for (int depth = 1; depth <= n; depth++) {
		dfs(depth, 1);
	}


	
	return 0;
}
