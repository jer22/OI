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
#include <bits/stdc++.h>

using namespace std;

int n;
long long m;
long long arr[100005];
long long temp[100005];
bool solve(long long mid) {
	for (int i = 1; i <= n; i++)
		temp[i] = arr[i];
	int pos = n;
	long long tot = 0;
	while (pos > 0) {
		while (!temp[pos] && pos) pos--;
		tot++;
		long long tim = mid - pos;

		if (tim <= 0 && temp[pos]) return false;
		while (tim >= temp[pos] && pos) {
			tim -= temp[pos];
			temp[pos--] = 0;
		}
		// cout << pos << endl;
		temp[pos] -= tim;
		if (tot > m) return false;
	}
	return tot <= m;
}

int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	long long l = 0, r = 2000000000000000;
	while (l < r) {
		long long mid = l + r >> 1;
		if (solve(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;
	// cout << solve(3);

	return 0;
}
