#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <deque>

using namespace std;

int main() {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	int T;
	scanf("%d", &T);
	string s;
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d: ", cas);
		cin >> s;
		int len = s.size();
		deque<char> ans;
		ans.push_back(s[0]);
		for (int i = 1; i < len; i++) {
			if (s[i] >= ans.front()) ans.push_front(s[i]);
			else ans.push_back(s[i]);
		}
		while (!ans.empty()) {
			cout << ans.front();
			ans.pop_front();
		}
		cout << endl;
	}


	return 0;
}
