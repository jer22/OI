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

int n, m;
char arr[55][55];
char temp[5];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		scanf("%s", arr[i] + 1);
	int ans = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			temp[0] = arr[i][j], temp[1] = arr[i + 1][j], temp[2] = arr[i][j + 1], temp[3] = arr[i + 1][j + 1];
			sort(temp, temp + 4);
			if (temp[0] == 'a' && temp[1] == 'c' && temp[2] == 'e' && temp[3] == 'f') ans++;
		}
	}
	cout << ans << endl;

	return 0;
}
