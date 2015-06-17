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
char arr[105][105];
int t[105];
int cnt[105];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%s", arr[i] + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (arr[j][i] == '1') cnt[i]++;
		}
	}
	for (int i = 1; i <= n; i++)
		cin >> t[i];
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		// cout << cnt[i] << endl;
		if (t[i] != 1) {
			flag = false;
			cout << "1" << endl;
			cout << i << endl;
			break;
		}
	}
	if (flag) {
		cout << "0" << endl;
	}
	return 0;
}
