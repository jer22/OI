/*
ID:shijiey1
PROG:shuttle
LANG:C++
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
