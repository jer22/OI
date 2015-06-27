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

struct Node{
	int val, pos;
	bool operator < (const Node &n) const {
		return val > n.val;
	}
};

int n;
Node arr[2005];
map<int, int> vis;
int ans[2005];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].val;
		arr[i].pos = i;
	}
	sort(arr + 1, arr + n + 1);
	int tot = 0;
	for (int i = 1; i <= n; i++) {		
		int t = arr[i].val;
		if (vis[t]) {
			ans[arr[i].pos] = vis[t];
			tot++;
		}
		else {
			vis[t] = ++tot;
			ans[arr[i].pos] = tot;
		}
	}
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];
	return 0;
}
