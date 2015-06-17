/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const long long MOD = 998244353;

int T, n;
int arr[50005];
int nex[2000005][2];
long long cnt[2000005];
int tot, root;

int lowbit(int x) {
	return x & -x;
}

void insert(int x) {
	int pos = root;
	for (int i = 0; i < 31; i++) {
		int t = x & 1;
		if (!nex[pos][t])
			nex[pos][t] = ++tot;
		pos = nex[pos][t];
		cnt[pos]++;
		x >>= 1;
	}
}

long long ans;

void solve(int x) {
	int pos = root;
	int cur = 1;
	for (int i = 0; i < 31; i++) {
		int t = x & 1;
		ans += cur * cnt[nex[pos][t ^ 1]];
		pos = nex[pos][t];
		x >>= 1;
		cur <<= 1;
	}
}

int main() {
	freopen("b.in", "r", stdin);
	cin >> T;
	int cas = 1;
	while (T--) {
		cin >> n;
		tot = root = 0;
		ans = 0;
		long long t = 0;
		memset(nex, 0, sizeof(nex));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			t += 2 * lowbit(arr[i]);
			t %= MOD;
		}
		for (int i = 1; i <= n; i++) {
			if (!arr[i]) {
				ans += t;
				ans %= MOD;
			}
			else {
				insert(arr[i]);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (!arr[i]) continue;
			solve(arr[i]);
		}
		// cout << tot << endl;
		printf("Case #%d: ", cas++);
		cout << ans % MOD << endl;
	}


	return 0;
}
