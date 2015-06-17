
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
bool arr[100005];
int main() {
	// freopen("e.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	if (arr[n]) {
		cout << "NO" << endl;
		return 0;
	}
	if (n == 1) {
		cout << "YES" << endl;
		cout << "0" << endl;
		return 0;
	}
	if (n == 2 && !arr[1]) {
		cout << "NO" << endl;
		return 0;
	}
	if (arr[n - 1]) {
		cout << "YES" << endl;
		for (int i = 1; i <= n; i++) {
			cout << arr[i];
			if (i != n) cout << "->";
			else cout << endl;
		}
	} else {
		if (n == 3) {
			if (arr[1]) {
				cout << "NO" << endl;
				return 0;
			} else {
				cout << "YES" << endl;
				cout << "0->0->0" << endl;
				return 0;
			}
		} else {
			if (!arr[n - 2]) {
				cout << "YES" << endl;
				for (int i = 1; i <= n - 3; i++) {
					cout << arr[i] << "->";
				}
				cout << "(0->0)->0" << endl;
				return 0;
			} else {
				bool flag = 1;
				for (int i = 1; i <= n - 3; i++)
					flag &= arr[i];
				if (flag) {
					cout << "NO" << endl;
					return 0;
				}
				cout << "YES" << endl;
				int i;
				for (i = 1; i <= n - 3; i++) {
					cout << arr[i] << "->";
					if (!arr[i]) break;
				}
				cout << "(";
				for (int j = i + 1; j <= n - 1; j++) {
					cout << arr[j];
					if (j != n - 1) cout << "->";
				}
				cout << ")";
				cout << "->0" << endl;
			}
		}
	}


	return 0;
}
