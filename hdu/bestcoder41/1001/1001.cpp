#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int T;
string str[6];
map<string, bool> vis;

string get(int a) {
	char gg[5];
	int top = 0;
	while (a) {
		gg[top++] = a % 10 + '0';
		a /= 10;
	}
	string ans = "";
	while (top--) {
		ans += gg[top];
	}
	return ans;
}

int solve() {
	int ans = 100000;
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 10; j++) {
			int t = 0;
			for (int k = 0; k < 5; k++) {
				char c = 'A' + i;
				int dd = j + k;
				if (dd == 14) dd = 1;
				string d = get(dd);
				string s = "";
				s += c;
				s += d;
				if (!vis[s]) t++;
			}
			ans = min(ans, t);
		}
	}
	return ans;
}

int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		vis.clear();
		for (int i = 1; i <= 5; i++) {
			cin >> str[i];
			vis[str[i]] = 1;
		}
		cout << solve() << endl;

	}

	return 0;
}
