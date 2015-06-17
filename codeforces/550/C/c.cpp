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

string str;

bool fuck(string s) {
	int t = 0;
	for (int i = 0; i < s.size(); i++) {
		t *= 10;
		t += s[i] - '0';
	}
	return !(t % 8);
}

bool dfs(int step, int idx, int num) {
	if (step > 3) return false;
	if (step) {
		if (!(num % 8)) {
			cout << "YES" << endl << num << endl;
			return true;
		}
	}
	for (int i = idx + 1; i < str.size(); i++) {
		int t = str[i] - '0';
		if (dfs(step + 1, i, num * 10 + t))
			return true;
	}
	return false;
}

int main() {
	// freopen("c.in", "r", stdin);
	cin >> str;
	if (str.size() == 1) {
		if (!fuck(str)) cout << "NO" << endl;
		else cout << "YES" << endl << str << endl;
	} else if (str.size() == 2) {
		int a = str[0] - '0';
		int b = str[1] - '0';
		if (!(a % 8)) {
			cout << "YES" << endl << a << endl;
		} else if (!(b % 8)) {
			cout << "YES" << endl << b << endl;
		} else {
			if (!fuck(str)) cout << "NO" << endl;
			else cout << "YES" << endl << str << endl;
		}
	} else {
		if (!dfs(0, -1, 0))
			cout << "NO" << endl;
	}


	return 0;
}
