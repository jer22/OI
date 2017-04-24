#include <bits/stdc++.h>

using namespace std;

string s;
int main() {
	freopen("b.in", "r", stdin);
	cin >> s;
	string ans = s;
	stack<int> stk;
	strint tmp;
	while (true) {
		int siz = s.size();
		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < siz; i++) {
			if (s[i] == '(') {
				stk.push(i);
				cnt
			} else if (s[i] == ')') {
				int pre = stk.top();
				stk.pop();
				tmp = "";
				


			} else if (s[i] == '+' || s[i] == '-') {

			} else if (s[i] == '*' || s[i] == '/') {

			}
		}
	}


	return 0;
}
