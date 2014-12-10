/*
ID:shijiey1
PROG:shuttle
LANG:C++
*/

/*
找规律。
4 35 642 1357 642 35 4 (n=3)

5 46 753 2468 97531 2468 753 46 5 (n=4)
其实就是n*2+1组等差数列。
先求出1到n+1组，然后根据对称性求出剩下的。
可以观察到：奇数组为降序，偶数组为升序；奇数组首项为n+i，偶数组首项为n-i+2。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int n;
int main() {
	freopen("shuttle.in", "r", stdin);
	freopen("shuttle.out", "w", stdout);
	int cnt = 0;
	scanf("%d", &n);
	stack<vector<int> > ans;
	for (int i = 2; i <= n + 1; i++) {
		vector<int> s;
		if (i % 2) {
			for (int j = n + i; j >= n - i + 2; j-= 2) {
				s.push_back(j);
			}
		} else {
			for (int j = n - i + 2; j <= n + i; j+= 2) {
				s.push_back(j);
			}
		}
		int l = s.size();
		for (int i = 0; i < l; i++) {
			cout << s[i];
			cnt++;
			if (!(cnt % 20)) {
				cout << endl;
			} else cout << ' ';
		}
		ans.push(s);
	}
	ans.pop();
	while (!ans.empty()) {
		vector<int> s = ans.top();
		ans.pop();
		int l = s.size();
		for (int i = 0; i < l; i++) {
			cout << s[i];
			cnt++;
			if (!(cnt % 20)) {
				cout << endl;
			} else cout << ' ';
		}
	}
	cout << n + 1 << endl;
	return 0;
}
